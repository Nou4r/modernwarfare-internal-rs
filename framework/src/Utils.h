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

#ifdef DEBUG_READ
    bool is_bad_ptr(auto p) {
        static_assert(sizeof(decltype(p)) == 8);
        MEMORY_BASIC_INFORMATION mbi = {0};
        if (::VirtualQuery(reinterpret_cast<LPCVOID>(p), &mbi, sizeof(mbi)))
        {
            DWORD mask = (PAGE_READONLY|PAGE_READWRITE|PAGE_WRITECOPY|PAGE_EXECUTE_READ|PAGE_EXECUTE_READWRITE|PAGE_EXECUTE_WRITECOPY);
            bool b = !(mbi.Protect & mask);
            // check the page is not a guard page
            if (mbi.Protect & (PAGE_GUARD|PAGE_NOACCESS)) b = true;

            return b;
        }
        return true;
    }
#else
    bool is_bad_ptr(auto p) {
        return !((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000);
    }
#endif

    int random_int(int, int);

    int find_string(const std::string &, const std::string &&);

    std::string base64_decode(const std::string &);

    std::string base64_encode(const std::string &);

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