#pragma once

#include <Windows.h>
#include <cstdint>
#include <string_view>
#include <numbers>

#define OFFSET(type, func, offset) type& func { return *reinterpret_cast<type*>( reinterpret_cast<uintptr_t>( this ) + offset ); }  // NOLINT
#define RESOLVE_RVA(Instr) (((DWORD64)(Instr)) + (7) + *(LONG*)(((DWORD64)(Instr)) + ((7) - sizeof(LONG))))
#define RAD2DEG(x)  ( ( float )( x ) * ( float )( 180.f / PI ) )
#define DEG2RAD(x)  ( ( float )( x ) * ( float )( ( float )PI / 180.f ) )

namespace utils
{
    uint8_t *find_pattern(const char *, const char *module_name = "ModernWarfare.exe");

    extern "C" bool is_bad_ptr(std::uintptr_t p);

    constexpr auto deg2rad(float degrees) noexcept
    { return degrees * (std::numbers::pi_v<float> / 180.0f); }

    constexpr auto rad2deg(float radians) noexcept
    { return radians * (180.0f / std::numbers::pi_v<float>); }

    template<size_t index, typename ret, class ... args_>
    __forceinline ret get_vfunc(void *thisptr, args_... args)
    {
        using fn = ret(__thiscall *)(void *, args_...);

        auto fn_ptr = reinterpret_cast<fn>((*static_cast<uintptr_t **>(thisptr))[index]);
        return fn_ptr(thisptr, args...);
    }
}