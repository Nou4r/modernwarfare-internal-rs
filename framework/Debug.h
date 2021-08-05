#pragma once

#include <Windows.h>
#include <format>
#include "xorstr.h"

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_ERROR(msg) MessageBoxA(0, _(msg), _("Error"), MB_OK);
#define DEBUG_INFO(msg, ...) OutputDebugString(std::format(_("[modernwarfare-internal] [{}:{}] " msg), __FILENAME__, __LINE__, __VA_ARGS__).c_str())
