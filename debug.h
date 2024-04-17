#pragma once

#include <string>
#include <dxgiformat.h>
#include <dxgicommon.h>

std::wstring EnumerateDxgiFormat(const DXGI_FORMAT Format);

std::wstring EnumerateDxgiColourSpace(const DXGI_COLOR_SPACE_TYPE ColourSpace);
