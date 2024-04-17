
#include "pch.h"
#include "debug.h"

std::wstring EnumerateDxgiFormat(const DXGI_FORMAT Format)
{
    switch(Format)
    {
        case DXGI_FORMAT_UNKNOWN:
        {
            return L"DXGI_FORMAT_UNKNOWN";
        }
        case DXGI_FORMAT_R32G32B32A32_TYPELESS:
        {
            return L"DXGI_FORMAT_R32G32B32A32_TYPELESS";
        }
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
        {
            return L"DXGI_FORMAT_R32G32B32A32_FLOAT";
        }
        case DXGI_FORMAT_R32G32B32A32_UINT:
        {
            return L"DXGI_FORMAT_R32G32B32A32_UINT";
        }
        case DXGI_FORMAT_R32G32B32A32_SINT:
        {
            return L"DXGI_FORMAT_R32G32B32A32_SINT";
        }
        case DXGI_FORMAT_R32G32B32_TYPELESS:
        {
            return L"DXGI_FORMAT_R32G32B32_TYPELESS";
        }
        case DXGI_FORMAT_R32G32B32_FLOAT:
        {
            return L"DXGI_FORMAT_R32G32B32_FLOAT";
        }
        case DXGI_FORMAT_R32G32B32_UINT:
        {
            return L"DXGI_FORMAT_R32G32B32_UINT";
        }
        case DXGI_FORMAT_R32G32B32_SINT:
        {
            return L"DXGI_FORMAT_R32G32B32_SINT";
        }
        case DXGI_FORMAT_R16G16B16A16_TYPELESS:
        {
            return L"DXGI_FORMAT_R16G16B16A16_TYPELESS";
        }
        case DXGI_FORMAT_R16G16B16A16_FLOAT:
        {
            return L"DXGI_FORMAT_R16G16B16A16_FLOAT";
        }
        case DXGI_FORMAT_R16G16B16A16_UNORM:
        {
            return L"DXGI_FORMAT_R16G16B16A16_UNORM";
        }
        case DXGI_FORMAT_R16G16B16A16_UINT:
        {
            return L"DXGI_FORMAT_R16G16B16A16_UINT";
        }
        case DXGI_FORMAT_R16G16B16A16_SNORM:
        {
            return L"DXGI_FORMAT_R16G16B16A16_SNORM";
        }
        case DXGI_FORMAT_R16G16B16A16_SINT:
        {
            return L"DXGI_FORMAT_R16G16B16A16_SINT";
        }
        case DXGI_FORMAT_R32G32_TYPELESS:
        {
            return L"DXGI_FORMAT_R32G32_TYPELESS";
        }
        case DXGI_FORMAT_R32G32_FLOAT:
        {
            return L"DXGI_FORMAT_R32G32_FLOAT";
        }
        case DXGI_FORMAT_R32G32_UINT:
        {
            return L"DXGI_FORMAT_R32G32_UINT";
        }
        case DXGI_FORMAT_R32G32_SINT:
        {
            return L"DXGI_FORMAT_R32G32_SINT";
        }
        case DXGI_FORMAT_R32G8X24_TYPELESS:
        {
            return L"DXGI_FORMAT_R32G8X24_TYPELESS";
        }
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        {
            return L"DXGI_FORMAT_D32_FLOAT_S8X24_UINT";
        }
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        {
            return L"DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS";
        }
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
        {
            return L"DXGI_FORMAT_X32_TYPELESS_G8X24_UINT";
        }
        case DXGI_FORMAT_R10G10B10A2_TYPELESS:
        {
            return L"DXGI_FORMAT_R10G10B10A2_TYPELESS";
        }
        case DXGI_FORMAT_R10G10B10A2_UNORM:
        {
            return L"DXGI_FORMAT_R10G10B10A2_UNORM";
        }
        case DXGI_FORMAT_R10G10B10A2_UINT:
        {
            return L"DXGI_FORMAT_R10G10B10A2_UINT";
        }
        case DXGI_FORMAT_R11G11B10_FLOAT:
        {
            return L"DXGI_FORMAT_R11G11B10_FLOAT";
        }
        case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        {
            return L"DXGI_FORMAT_R8G8B8A8_TYPELESS";
        }
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        {
            return L"DXGI_FORMAT_R8G8B8A8_UNORM";
        }
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        {
            return L"DXGI_FORMAT_R8G8B8A8_UNORM_SRGB";
        }
        case DXGI_FORMAT_R8G8B8A8_UINT:
        {
            return L"DXGI_FORMAT_R8G8B8A8_UINT";
        }
        case DXGI_FORMAT_R8G8B8A8_SNORM:
        {
            return L"DXGI_FORMAT_R8G8B8A8_SNORM";
        }
        case DXGI_FORMAT_R8G8B8A8_SINT:
        {
            return L"DXGI_FORMAT_R8G8B8A8_SINT";
        }
        case DXGI_FORMAT_R16G16_TYPELESS:
        {
            return L"DXGI_FORMAT_R16G16_TYPELESS";
        }
        case DXGI_FORMAT_R16G16_FLOAT:
        {
            return L"DXGI_FORMAT_R16G16_FLOAT";
        }
        case DXGI_FORMAT_R16G16_UNORM:
        {
            return L"DXGI_FORMAT_R16G16_UNORM";
        }
        case DXGI_FORMAT_R16G16_UINT:
        {
            return L"DXGI_FORMAT_R16G16_UINT";
        }
        case DXGI_FORMAT_R16G16_SNORM:
        {
            return L"DXGI_FORMAT_R16G16_SNORM";
        }
        case DXGI_FORMAT_R16G16_SINT:
        {
            return L"DXGI_FORMAT_R16G16_SINT";
        }
        case DXGI_FORMAT_R32_TYPELESS:
        {
            return L"DXGI_FORMAT_R32_TYPELESS";
        }
        case DXGI_FORMAT_D32_FLOAT:
        {
            return L"DXGI_FORMAT_D32_FLOAT";
        }
        case DXGI_FORMAT_R32_FLOAT:
        {
            return L"DXGI_FORMAT_R32_FLOAT";
        }
        case DXGI_FORMAT_R32_UINT:
        {
            return L"DXGI_FORMAT_R32_UINT";
        }
        case DXGI_FORMAT_R32_SINT:
        {
            return L"DXGI_FORMAT_R32_SINT";
        }
        case DXGI_FORMAT_R24G8_TYPELESS:
        {
            return L"DXGI_FORMAT_R24G8_TYPELESS";
        }
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
        {
            return L"DXGI_FORMAT_D24_UNORM_S8_UINT";
        }
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        {
            return L"DXGI_FORMAT_R24_UNORM_X8_TYPELESS";
        }
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        {
            return L"DXGI_FORMAT_X24_TYPELESS_G8_UINT";
        }
        case DXGI_FORMAT_R8G8_TYPELESS:
        {
            return L"DXGI_FORMAT_R8G8_TYPELESS";
        }
        case DXGI_FORMAT_R8G8_UNORM:
        {
            return L"DXGI_FORMAT_R8G8_UNORM";
        }
        case DXGI_FORMAT_R8G8_UINT:
        {
            return L"DXGI_FORMAT_R8G8_UINT";
        }
        case DXGI_FORMAT_R8G8_SNORM:
        {
            return L"DXGI_FORMAT_R8G8_SNORM";
        }
        case DXGI_FORMAT_R8G8_SINT:
        {
            return L"DXGI_FORMAT_R8G8_SINT";
        }
        case DXGI_FORMAT_R16_TYPELESS:
        {
            return L"DXGI_FORMAT_R16_TYPELESS";
        }
        case DXGI_FORMAT_R16_FLOAT:
        {
            return L"DXGI_FORMAT_R16_FLOAT";
        }
        case DXGI_FORMAT_D16_UNORM:
        {
            return L"DXGI_FORMAT_D16_UNORM";
        }
        case DXGI_FORMAT_R16_UNORM:
        {
            return L"DXGI_FORMAT_R16_UNORM";
        }
        case DXGI_FORMAT_R16_UINT:
        {
            return L"DXGI_FORMAT_R16_UINT";
        }
        case DXGI_FORMAT_R16_SNORM:
        {
            return L"DXGI_FORMAT_R16_SNORM";
        }
        case DXGI_FORMAT_R16_SINT:
        {
            return L"DXGI_FORMAT_R16_SINT";
        }
        case DXGI_FORMAT_R8_TYPELESS:
        {
            return L"DXGI_FORMAT_R8_TYPELESS";
        }
        case DXGI_FORMAT_R8_UNORM:
        {
            return L"DXGI_FORMAT_R8_UNORM";
        }
        case DXGI_FORMAT_R8_UINT:
        {
            return L"DXGI_FORMAT_R8_UINT";
        }
        case DXGI_FORMAT_R8_SNORM:
        {
            return L"DXGI_FORMAT_R8_SNORM";
        }
        case DXGI_FORMAT_R8_SINT:
        {
            return L"DXGI_FORMAT_R8_SINT";
        }
        case DXGI_FORMAT_A8_UNORM:
        {
            return L"DXGI_FORMAT_A8_UNORM";
        }
        case DXGI_FORMAT_R1_UNORM:
        {
            return L"DXGI_FORMAT_R1_UNORM";
        }
        case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
        {
            return L"DXGI_FORMAT_R9G9B9E5_SHAREDEXP";
        }
        case DXGI_FORMAT_R8G8_B8G8_UNORM:
        {
            return L"DXGI_FORMAT_R8G8_B8G8_UNORM";
        }
        case DXGI_FORMAT_G8R8_G8B8_UNORM:
        {
            return L"DXGI_FORMAT_G8R8_G8B8_UNORM";
        }
        case DXGI_FORMAT_BC1_TYPELESS:
        {
            return L"DXGI_FORMAT_BC1_TYPELESS";
        }
        case DXGI_FORMAT_BC1_UNORM:
        {
            return L"DXGI_FORMAT_BC1_UNORM";
        }
        case DXGI_FORMAT_BC1_UNORM_SRGB:
        {
            return L"DXGI_FORMAT_BC1_UNORM_SRGB";
        }
        case DXGI_FORMAT_BC2_TYPELESS:
        {
            return L"DXGI_FORMAT_BC2_TYPELESS";
        }
        case DXGI_FORMAT_BC2_UNORM:
        {
            return L"DXGI_FORMAT_BC2_UNORM";
        }
        case DXGI_FORMAT_BC2_UNORM_SRGB:
        {
            return L"DXGI_FORMAT_BC2_UNORM_SRGB";
        }
        case DXGI_FORMAT_BC3_TYPELESS:
        {
            return L"DXGI_FORMAT_BC3_TYPELESS";
        }
        case DXGI_FORMAT_BC3_UNORM:
        {
            return L"DXGI_FORMAT_BC3_UNORM";
        }
        case DXGI_FORMAT_BC3_UNORM_SRGB:
        {
            return L"DXGI_FORMAT_BC3_UNORM_SRGB";
        }
        case DXGI_FORMAT_BC4_TYPELESS:
        {
            return L"DXGI_FORMAT_BC4_TYPELESS";
        }
        case DXGI_FORMAT_BC4_UNORM:
        {
            return L"DXGI_FORMAT_BC4_UNORM";
        }
        case DXGI_FORMAT_BC4_SNORM:
        {
            return L"DXGI_FORMAT_BC4_SNORM";
        }
        case DXGI_FORMAT_BC5_TYPELESS:
        {
            return L"DXGI_FORMAT_BC5_TYPELESS";
        }
        case DXGI_FORMAT_BC5_UNORM:
        {
            return L"DXGI_FORMAT_BC5_UNORM";
        }
        case DXGI_FORMAT_BC5_SNORM:
        {
            return L"DXGI_FORMAT_BC5_SNORM";
        }
        case DXGI_FORMAT_B5G6R5_UNORM:
        {
            return L"DXGI_FORMAT_B5G6R5_UNORM";
        }
        case DXGI_FORMAT_B5G5R5A1_UNORM:
        {
            return L"DXGI_FORMAT_B5G5R5A1_UNORM";
        }
        case DXGI_FORMAT_B8G8R8A8_UNORM:
        {
            return L"DXGI_FORMAT_B8G8R8A8_UNORM";
        }
        case DXGI_FORMAT_B8G8R8X8_UNORM:
        {
            return L"DXGI_FORMAT_B8G8R8X8_UNORM";
        }
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        {
            return L"DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM";
        }
        case DXGI_FORMAT_B8G8R8A8_TYPELESS:
        {
            return L"DXGI_FORMAT_B8G8R8A8_TYPELESS";
        }
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        {
            return L"DXGI_FORMAT_B8G8R8A8_UNORM_SRGB";
        }
        case DXGI_FORMAT_B8G8R8X8_TYPELESS:
        {
            return L"DXGI_FORMAT_B8G8R8X8_TYPELESS";
        }
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        {
            return L"DXGI_FORMAT_B8G8R8X8_UNORM_SRGB";
        }
        case DXGI_FORMAT_BC6H_TYPELESS:
        {
            return L"DXGI_FORMAT_BC6H_TYPELESS";
        }
        case DXGI_FORMAT_BC6H_UF16:
        {
            return L"DXGI_FORMAT_BC6H_UF16";
        }
        case DXGI_FORMAT_BC6H_SF16:
        {
            return L"DXGI_FORMAT_BC6H_SF16";
        }
        case DXGI_FORMAT_BC7_TYPELESS:
        {
            return L"DXGI_FORMAT_BC7_TYPELESS";
        }
        case DXGI_FORMAT_BC7_UNORM:
        {
            return L"DXGI_FORMAT_BC7_UNORM";
        }
        case DXGI_FORMAT_BC7_UNORM_SRGB:
        {
            return L"DXGI_FORMAT_BC7_UNORM_SRGB";
        }
        case DXGI_FORMAT_AYUV:
        {
            return L"DXGI_FORMAT_AYUV";
        }
        case DXGI_FORMAT_Y410:
        {
            return L"DXGI_FORMAT_Y410";
        }
        case DXGI_FORMAT_Y416:
        {
            return L"DXGI_FORMAT_Y416";
        }
        case DXGI_FORMAT_NV12:
        {
            return L"DXGI_FORMAT_NV12";
        }
        case DXGI_FORMAT_P010:
        {
            return L"DXGI_FORMAT_P010";
        }
        case DXGI_FORMAT_P016:
        {
            return L"DXGI_FORMAT_P016";
        }
        case DXGI_FORMAT_420_OPAQUE:
        {
            return L"DXGI_FORMAT_420_OPAQUE";
        }
        case DXGI_FORMAT_YUY2:
        {
            return L"DXGI_FORMAT_YUY2";
        }
        case DXGI_FORMAT_Y210:
        {
            return L"DXGI_FORMAT_Y210";
        }
        case DXGI_FORMAT_Y216:
        {
            return L"DXGI_FORMAT_Y216";
        }
        case DXGI_FORMAT_NV11:
        {
            return L"DXGI_FORMAT_NV11";
        }
        case DXGI_FORMAT_AI44:
        {
            return L"DXGI_FORMAT_AI44";
        }
        case DXGI_FORMAT_IA44:
        {
            return L"DXGI_FORMAT_IA44";
        }
        case DXGI_FORMAT_P8:
        {
            return L"DXGI_FORMAT_P8";
        }
        case DXGI_FORMAT_A8P8:
        {
            return L"DXGI_FORMAT_A8P8";
        }
        case DXGI_FORMAT_B4G4R4A4_UNORM:
        {
            return L"DXGI_FORMAT_B4G4R4A4_UNORM";
        }
        case DXGI_FORMAT_P208:
        {
            return L"DXGI_FORMAT_P208";
        }
        case DXGI_FORMAT_V208:
        {
            return L"DXGI_FORMAT_V208";
        }
        case DXGI_FORMAT_V408:
        {
            return L"DXGI_FORMAT_V408";
        }
        case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
        {
            return L"DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE";
        }
        case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
        {
            return L"DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE";
        }
        default:
        {
            return L"unknown DXGI format";
        }
    }
}

std::wstring EnumerateDxgiColourSpace(const DXGI_COLOR_SPACE_TYPE ColourSpace)
{
    switch(ColourSpace)
    {
        case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709:
        {
            return L"DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709";
        }
        case DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709:
        {
            return L"DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709";
        }
        case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709:
        {
            return L"DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709";
        }
        case DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020:
        {
            return L"DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020";
        }
        case DXGI_COLOR_SPACE_RESERVED:
        {
            return L"DXGI_COLOR_SPACE_RESERVED";
        }
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601";
        }
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709";
        }
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020";
        }
        case DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020:
        {
            return L"DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020";
        }
        case DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020:
        {
            return L"DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020";
        }
        case DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020:
        {
            return L"DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020";
        }
        case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709:
        {
            return L"DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709";
        }
        case DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020:
        {
            return L"DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020";
        }
        case DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020:
        {
            return L"DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020";
        }
        case DXGI_COLOR_SPACE_CUSTOM:
        {
            return L"DXGI_COLOR_SPACE_CUSTOM";
        }
        default:
        {
            return L"unknown DXGI colour space";
        }
    }
}
