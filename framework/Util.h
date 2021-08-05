#pragma once

#include <cstdint>

#include "Debug.h"
#include "xorstr.h"

namespace utils
{
	inline bool isBadPtr(std::uintptr_t p)
	{
		return !(p <= 0x7FFFFFFEFFFF && p >= 0x1000);
	}

	uint8_t* findPattern(const char* moduleName, const char* pattern);
}

template<typename T>
inline auto readMemory(uintptr_t ptr) noexcept -> T {
	if(utils::isBadPtr(ptr)) {
			DEBUG_INFO("Attempted to read invalid memory at {:#x}", ptr);
			return {};
		}
	return *reinterpret_cast<T*>(ptr);
}
