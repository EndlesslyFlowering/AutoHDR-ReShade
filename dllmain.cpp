#include "pch.h"

#define ImTextureID unsigned long long int

#include <stdio.h>
#include <imgui.h>
#include <reshade.hpp>
#include <dxgi1_6.h>
#include <d3d11.h>
#include <d3d12.h>
#include <mutex>
#include <sstream>
#include <unordered_set>
#include <cassert>
#include <atlbase.h>


//#define __WINRT__

std::unordered_set<uint64_t> g_back_buffers;
std::mutex g_mutex;

#define USE_HDR10 false
#define USE_SCRGB true

bool                    g_hdr_enable            = false;
bool                    g_use_scrgb             = USE_HDR10;
bool                    g_hdr_support           = false;
bool                    g_hdr_enabled           = false;
DXGI_COLOR_SPACE_TYPE   g_colour_space          = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;

reshade::api::device*   g_device                = nullptr;

inline static int dxgi_compute_intersection_area(
    int ax1, int ay1, int ax2, int ay2,
    int bx1, int by1, int bx2, int by2)
{
    return  max(0, min(ax2, bx2) -
            max(ax1, bx1))
            * max(0, min(ay2, by2) - max(ay1, by1));
}

#if _DEBUG
class LogManager
{
public:
    LogManager()
    {
        errno_t error = _wfopen_s(&log_file, L"log.txt", L"w");
    }

    ~LogManager()
    {
        fclose(log_file);
    }

    inline void Message(LPCWSTR format, va_list& args)
    {
        OutputDebugString(format);
        WriteWideFormatted(log_file, format, args);
    }

private:

    void WriteWideFormatted(FILE* stream, LPCWSTR format, va_list& args)
    {
        vfwprintf(stream, format, args);
    }

    FILE* log_file = nullptr;
};

static LogManager g_log;
#endif // _DEBUG

inline void Log(LPCWSTR format, ...)
{
#if _DEBUG
    va_list args;
    va_start(args, format);
    g_log.Message(format, args);
    va_end(args);
#endif // _DEBUG
}

#ifdef __WINRT__
bool dxgi_check_display_hdr_support(IDXGIFactory2* factory, HWND hwnd)
#else
bool dxgi_check_display_hdr_support(IDXGIFactory1* factory, HWND hwnd)
#endif
{
    IDXGIOutput6* output6 = NULL;
    IDXGIOutput* best_output = NULL;
    IDXGIOutput* current_output = NULL;
    IDXGIAdapter* dxgi_adapter = NULL;
    UINT i = 0;
    bool supported = false;
    float best_intersect_area = -1;

#ifdef __WINRT__
    if (!factory->IsCurrent())
    {
        if (FAILED(CreateDXGIFactory2(0, __uuidof(IDXGIFactory2), (void**)&factory)))
        {
            Log (L"[DXGI]: Failed to create DXGI factory\n");
            return false;
        }
    }

    if (FAILED(factory->EnumAdapters(0, &dxgi_adapter)))
    {
        Log (L"[DXGI]: Failed to enumerate adapters\n");
        return false;
    }
#else
    if (!factory->IsCurrent())
    {
        if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
        {
            Log (L"[DXGI]: Failed to create DXGI factory\n");
            return false;
        }
    }

    if (FAILED(factory->EnumAdapters(0, &dxgi_adapter)))
    {
        Log (L"[DXGI]: Failed to enumerate adapters\n");
        return false;
    }
#endif

    while (dxgi_adapter->EnumOutputs(i, &current_output)
        != DXGI_ERROR_NOT_FOUND)
    {
        RECT r, rect;
        DXGI_OUTPUT_DESC desc;
        int intersect_area;
        int bx1, by1, bx2, by2;
        int ax1 = 0;
        int ay1 = 0;
        int ax2 = 0;
        int ay2 = 0;

        if (GetWindowRect(hwnd, &rect))
        {
            ax1 = rect.left;
            ay1 = rect.top;
            ax2 = rect.right;
            ay2 = rect.bottom;
        }

        /* Get the rectangle bounds of current output */
        if (FAILED(current_output->GetDesc(&desc)))
        {
            Log (L"[DXGI]: Failed to get DXGI output description\n");
            goto error;
        }

        /* TODO/FIXME - DesktopCoordinates won't work for WinRT */
        r = desc.DesktopCoordinates;
        bx1 = r.left;
        by1 = r.top;
        bx2 = r.right;
        by2 = r.bottom;

        /* Compute the intersection */
        intersect_area = dxgi_compute_intersection_area(
            ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);

        if (intersect_area > best_intersect_area)
        {
            best_output = current_output;
            best_output->AddRef();
            best_intersect_area = (float)intersect_area;
        }

        i++;
    }

    if (SUCCEEDED(best_output->QueryInterface(__uuidof(IDXGIOutput6), (void**)&output6)))
    {
        DXGI_OUTPUT_DESC1 desc1;
        if (SUCCEEDED(output6->GetDesc1(&desc1)))
        {
            supported = (desc1.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020);

            if (supported)
            {
                Log(L"[DXGI]: DXGI Output supports: DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020\n");
            }

            g_hdr_support = supported;
        }
        else
        {
            Log (L"[DXGI]: Failed to get DXGI Output 6 description\n");
        }
        output6->Release();
    }
    else
    {
        Log (L"[DXGI]: Failed to get DXGI Output 6 from best output\n");
    }

error:
    if(best_output) best_output->Release();
    if(current_output) current_output->Release();
    if(dxgi_adapter) dxgi_adapter->Release();

    return supported;
}

void dxgi_swapchain_color_space(
    IDXGISwapChain3* swapchain,
    DXGI_COLOR_SPACE_TYPE* colour_space,
    DXGI_COLOR_SPACE_TYPE target_colour_space)
{
    if (*colour_space != target_colour_space)
    {
        UINT color_space_support = 0;
        HRESULT hr = swapchain->CheckColorSpaceSupport(target_colour_space, &color_space_support);

        if (FAILED(hr))
        {
            Log(L"[DXGI]: Failed to check DXGI swapchain colour space support\n");
            return;
        }

        if((color_space_support & DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT) == DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT)
        {
            if (FAILED(swapchain->SetColorSpace1(target_colour_space)))
            {
                Log (L"[DXGI]: Failed to set DXGI swapchain colour space\n");
                return;
            }

            *colour_space = target_colour_space;
        }
        else
        {
            Log(L"[DXGI]: DXGI swapchain colour space %d (%d) not supported\n", target_colour_space, color_space_support);
        }
    }
}

static void on_init_device(reshade::api::device* device)
{
    //device->create_private_data<state_tracking_context>();

    g_device = device;

    reshade::get_config_value(nullptr, "HDR", "EnableHDR", g_hdr_enable);
    reshade::get_config_value(nullptr, "HDR", "UseScrgb",  g_use_scrgb);
}

static void on_destroy_device(reshade::api::device* device)
{
    g_device = nullptr;
}

//static void init_swapchain(reshade::api::swapchain* swapchain)
//{
//    static int t = 0; ++t;
//}

static bool on_create_swapchain(reshade::api::swapchain_desc& swapchain_desc, void* hwnd)
{
    if (!g_use_scrgb)
    {
        swapchain_desc.back_buffer.texture.format = reshade::api::format::r10g10b10a2_unorm;
    }
    else
    {
        swapchain_desc.back_buffer.texture.format = reshade::api::format::r16g16b16a16_float;
    }

    //swapchain_desc.refresh_rate.numerator = 60;
    //swapchain_desc.refresh_rate.denominator = 1;

    if (swapchain_desc.back_buffer_count < 2)
    {
        swapchain_desc.back_buffer_count = 2;
    }

    if (g_device)
    {
        const reshade::api::device_api device_type = g_device->get_api();

        if ((device_type == reshade::api::device_api::d3d11) || (device_type == reshade::api::device_api::d3d12))
        {
            DXGI_SWAP_EFFECT swap_effect = static_cast<DXGI_SWAP_EFFECT>(swapchain_desc.present_mode);

            swap_effect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

            swapchain_desc.present_mode = static_cast<uint32_t>(swap_effect);

            swapchain_desc.present_flags |= static_cast<uint32_t>(DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING);
        }
    }

    return true;
}

static void on_init_swapchain(reshade::api::swapchain* swapchain)
{
    const std::lock_guard<std::mutex> lock(g_mutex);

    reshade::api::device* const device = swapchain->get_device();

    for (uint32_t i = 0; i < swapchain->get_back_buffer_count(); ++i)
    {
        const reshade::api::resource buffer = swapchain->get_back_buffer(i);

        g_back_buffers.emplace(buffer.handle);
    }
}

static void on_destroy_swapchain(reshade::api::swapchain* swapchain)
{
    const std::lock_guard<std::mutex> lock(g_mutex);

    reshade::api::device* const device = swapchain->get_device();

    for (uint32_t i = 0; i < swapchain->get_back_buffer_count(); ++i)
    {
        const reshade::api::resource buffer = swapchain->get_back_buffer(i);

        g_back_buffers.erase(buffer.handle);
    }
}

static bool on_create_resource_view(reshade::api::device* device, reshade::api::resource resource, reshade::api::resource_usage usage_type, reshade::api::resource_view_desc& desc)
{
    if ((desc.format != reshade::api::format::unknown) && device)
    {
        bool is_back_buffer = false;

        for (uint64_t back_buffer : g_back_buffers)
        {
            if (resource == back_buffer)
            {
                is_back_buffer = true;
            }
        }

        if (is_back_buffer)
        {
            const reshade::api::resource_desc texture_desc = device->get_resource_desc(resource);

            if (texture_desc.texture.format == reshade::api::format::r10g10b10a2_unorm)
            {
                desc.format = reshade::api::format::r10g10b10a2_unorm;
                return true;
            }

            if (texture_desc.texture.format == reshade::api::format::r16g16b16a16_float)
            {
                desc.format = reshade::api::format::r16g16b16a16_float;
                return true;
            }
        }
    }
    return false;
}

static void on_present(reshade::api::command_queue* queue, reshade::api::swapchain* swapchain, const reshade::api::rect* source_rect, const reshade::api::rect* dest_rect, uint32_t dirty_rect_count, const reshade::api::rect* dirty_rects)
{
    reshade::api::device* device    = swapchain->get_device();
    const reshade::api::device_api device_type = device->get_api();

    if((device_type == reshade::api::device_api::d3d11) || (device_type == reshade::api::device_api::d3d12))
    {
        IDXGISwapChain* native_swapchain = reinterpret_cast<IDXGISwapChain*>(swapchain->get_native());
        ATL::CComPtr<IDXGISwapChain4> swapchain4;

        if (SUCCEEDED(native_swapchain->QueryInterface(__uuidof(IDXGISwapChain4), (void**)&swapchain4)))
        {
            if (g_hdr_support == false)
            {
#ifdef __WINRT__
                IDXGIFactory2* factory = nullptr;
                if (FAILED(swapchain4->GetParent(__uuidof(IDXGIFactory2), (void**)&factory)))
                {
                    Log(L"[DXGI]: Failed to get the swap chain's factory 2\n");
                    return;
                }

                g_hdr_support = dxgi_check_display_hdr_support(factory, reinterpret_cast<HWND>(swapchain->get_hwnd()));
#else
                IDXGIFactory1* factory = nullptr;
                if (FAILED(swapchain4->GetParent(__uuidof(IDXGIFactory1), (void**)&factory)))
                {
                    Log(L"[DXGI]: Failed to get the swap chain's factory 1\n");
                    return;
                }

                g_hdr_support = dxgi_check_display_hdr_support(factory, reinterpret_cast<HWND>(swapchain->get_hwnd()));
                
                factory->Release();
#endif // __WINRT__
            }

            if (g_hdr_support == false)
            {
                Log(L"[DXGI]: Failed as no HDR support\n");
                return;
            }

            if ((g_hdr_enable == true) && (g_hdr_enabled == false))
            {
                DXGI_COLOR_SPACE_TYPE colour_space = DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;
                DXGI_FORMAT           swapchain_format = DXGI_FORMAT_R10G10B10A2_UNORM;

                if (g_use_scrgb)
                {
                    colour_space = DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709;
                    swapchain_format = DXGI_FORMAT_R16G16B16A16_FLOAT;
                }

                dxgi_swapchain_color_space(swapchain4, &g_colour_space, colour_space);

                DXGI_SWAP_CHAIN_DESC1 desc;
                if (FAILED(swapchain4->GetDesc1(&desc)))
                {
                    Log(L"[DXGI]: Failed to get swap chain description\n");
                    return;
                }

                if (swapchain_format != desc.Format)
                {
                    HRESULT hr = swapchain4->ResizeBuffers(
                        desc.BufferCount,
                        desc.Width,
                        desc.Height,
                        swapchain_format,
                        desc.Flags);

                    if (hr == DXGI_ERROR_INVALID_CALL) // Ignore invalid call errors since the device is still in a usable state afterwards
                    {
                        Log(L"[DXGI]: Failed to resize swap chain buffers DXGI_FORMAT_R8G8B8A8_UNORM: error DXGI_ERROR_INVALID_CALL\n");
                    }
                    else if (FAILED(hr))
                    {
                        Log(L"[DXGI]: Failed to resize swap chain buffers DXGI_FORMAT_R10G10B10A2_UNORM: error 0x%x\n", hr);
                        return;
                    }
                }

                g_hdr_enabled = true;
            }
            else if ((g_hdr_enable == false) && (g_hdr_enabled == true))
            {
                DXGI_COLOR_SPACE_TYPE colour_space = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;
                DXGI_FORMAT           swapchain_format = DXGI_FORMAT_R8G8B8A8_UNORM;

                dxgi_swapchain_color_space(swapchain4, &g_colour_space, colour_space);
                DXGI_SWAP_CHAIN_DESC1 desc;
                if (FAILED(swapchain4->GetDesc1(&desc)))
                {
                    Log(L"[DXGI]: Failed to get swap chain description\n");
                    return;
                }

                if (swapchain_format != desc.Format)
                {
                    HRESULT hr = swapchain4->ResizeBuffers(
                        desc.BufferCount,
                        desc.Width,
                        desc.Height,
                        swapchain_format,
                        desc.Flags);

                    if (hr == DXGI_ERROR_INVALID_CALL) // Ignore invalid call errors since the device is still in a usable state afterwards
                    {
                        Log(L"[DXGI]: Failed to resize swap chain buffers DXGI_FORMAT_R8G8B8A8_UNORM: error DXGI_ERROR_INVALID_CALL\n");
                    }
                    else if (FAILED(hr))
                    {
                        Log(L"[DXGI]: Failed to resize swap chain buffers DXGI_FORMAT_R8G8B8A8_UNORM: error 0x%x\n", hr);
                    }
                }

                g_hdr_enabled = false;
            }
        }
    }
}

static void draw_settings_overlay(reshade::api::effect_runtime* runtime)
{
    if (g_hdr_support)
    {
        bool hdr_enable_modified    = false;
        bool hdr_use_scrgb_modified = false;

        hdr_enable_modified    |= ImGui::Checkbox("Enable HDR", &g_hdr_enable);
        hdr_use_scrgb_modified |= ImGui::Checkbox("Use scRGB instead of HDR10 (needs game restart)", &g_use_scrgb);

        if (hdr_enable_modified)
        {
            reshade::set_config_value(nullptr, "HDR", "EnableHDR", g_hdr_enable);
        }
        if (hdr_use_scrgb_modified)
        {
            reshade::set_config_value(nullptr, "HDR", "UseScrgb", g_use_scrgb);
        }
    }
    else
    {
        ImGui::TextUnformatted("HDR support is not enabled. If hardware can support it please go to Windows 'Display Settings' and then turn on 'Use HDR'");
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Call 'reshade::register_addon()' before you call any other function of the ReShade API.
        // This will look for the ReShade instance in the current process and initialize the API when found.
        Log(L"dll attached\n");
        if (!reshade::register_addon(hinstDLL))
            return FALSE;
        Log(L"reshade addon registered\n");

        reshade::register_overlay(nullptr, draw_settings_overlay);
        // This registers a callback for the 'present' event, which occurs every time a new frame is presented to the screen.
        // The function signature has to match the type defined by 'reshade::addon_event_traits<reshade::addon_event::present>::decl'.
        // For more details check the inline documentation for each event in 'reshade_events.hpp'.
        reshade::register_event<reshade::addon_event::present>(&on_present);

        reshade::register_event<reshade::addon_event::create_swapchain>(&on_create_swapchain);
        reshade::register_event<reshade::addon_event::init_swapchain>(on_init_swapchain);
        reshade::register_event<reshade::addon_event::destroy_swapchain>(on_destroy_swapchain);

        reshade::register_event<reshade::addon_event::create_resource_view>(&on_create_resource_view);

        reshade::register_event<reshade::addon_event::init_device>(&on_init_device);
        reshade::register_event<reshade::addon_event::destroy_device>(&on_destroy_device);

        break;
    case DLL_PROCESS_DETACH:
        // Optionally unregister the event callback that was previously registered during process attachment again.
        reshade::unregister_event<reshade::addon_event::present>(&on_present);

        reshade::unregister_event<reshade::addon_event::create_swapchain>(&on_create_swapchain);
        reshade::unregister_event<reshade::addon_event::init_swapchain>(on_init_swapchain);
        reshade::unregister_event<reshade::addon_event::destroy_swapchain>(on_destroy_swapchain);

        reshade::unregister_event<reshade::addon_event::create_resource_view>(&on_create_resource_view);

        reshade::unregister_event<reshade::addon_event::init_device>(&on_init_device);
        reshade::unregister_event<reshade::addon_event::destroy_device>(&on_destroy_device);

        // And finally unregister the add-on from ReShade (this will automatically unregister any events and overlays registered by this add-on too).
        reshade::unregister_addon(hinstDLL);
        break;
    }
    return TRUE;
}