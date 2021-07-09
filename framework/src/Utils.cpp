#include "Utils.h"
#include "lazy_importer.h"
#include <random>
#include <sstream>
#include <vector>
#include <Windows.h>
#include "imgui.h"
#include "xorstr.h"

uint8_t* utils::find_pattern(const char* signature, const char* module_name)
{
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto* const start = const_cast<char*>(pattern);
        auto* const end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto* current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            } else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto* const module = LI_FN(GetModuleHandleA).cached()(module_name);
    auto* const dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
    if (!dos_headers)
        return nullptr;

    auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) +
                                                                 dos_headers->e_lfanew);

    auto pattern_bytes = pattern_to_byte(signature);
    auto* const scan_bytes = reinterpret_cast<std::uint8_t*>(module);

    const auto s = pattern_bytes.size();
    auto* const d = pattern_bytes.data();

    for (auto i = 0ul; i < nt_headers->OptionalHeader.SizeOfImage - s; ++i) {
        auto found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scan_bytes[i];
        }
    }
    return nullptr;
}


//#define DEBUG_READ

#ifndef DEBUG_READ

bool utils::is_bad_ptr(std::uintptr_t p)
{
    return !((uintptr_t) (p) <= 0x7FFFFFFEFFFF && (uintptr_t) (p) >= 0x1000);
}

#else

bool utils::is_bad_ptr(std::uintptr_t p)
{
    static_assert(sizeof(decltype(p)) == 8);
    MEMORY_BASIC_INFORMATION mbi = {0};
    if (::VirtualQuery(reinterpret_cast<LPCVOID>(p), &mbi, sizeof(mbi))) {
        DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE |
                      PAGE_EXECUTE_WRITECOPY);
        bool b = !(mbi.Protect & mask);
        // check the page is not a guard page
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

        return b;
    }
    return true;
}

#endif

#include "syscall.h"

extern "C" uint32_t move_mouse_relative(int dx, int dy) {
    INPUT input = {};

    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    // NtUserSendInput
    //      "1507": 4228,
    //      "1511": 4228,
    //      "1607": 4228,
    //      "1703": 4226,
    //      "1709": 4226,
    //      "1803": 4226,
    //      "1809": 4226,
    //      "1903": 4226,
    //      "1909": 4226,
    //      "2004": 4223,
    //      "20H2": 4223

    return do_syscall<ULONG>(4223, 1, &input, sizeof(INPUT));
}
