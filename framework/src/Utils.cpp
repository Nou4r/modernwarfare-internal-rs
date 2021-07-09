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

// HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\DisplayVersion
static std::string getVersion()
{
    DWORD dwType = REG_SZ;
    HKEY hKey = 0;
    char value[1024];
    DWORD value_length = 1024;
    const char* subkey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
    const auto status = RegQueryValueEx(hKey, "DisplayVersion", NULL, &dwType, (LPBYTE) &value, &value_length);
    return std::string(value);
}

extern "C" uint32_t move_mouse_relative(int dx, int dy)
{
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
    static auto version = getVersion();
    int id = 4223;
    if (version == "1507") {
        id = 4228;
    } else if (version == "1511") {
        id = 4228;
    } else if (version == "1607") {
        id = 4228;
    } else if (version == "1703") {
        id = 4226;
    } else if (version == "1709") {
        id = 4226;
    } else if (version == "1803") {
        id = 4226;
    } else if (version == "1809") {
        id = 4226;
    } else if (version == "1903") {
        id = 4226;
    } else if (version == "1909") {
        id = 4226;
    } else if (version == "2004") {
        id = 4223;
    } else if (version == "20H2") {
        id = 4223;
    }

    return do_syscall<ULONG>(4223, 1, &input, sizeof(INPUT));
}
