#include "Util.h"

#include <Windows.h>
#include <vector>

#include "lazy_importer.h"

uint8_t* utils::findPattern(const char* moduleName, const char* pattern)
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

    auto* const module = LI_FN(GetModuleHandleA).cached()(pattern);
    auto* const dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
    if (!dos_headers)
        return nullptr;

    auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) +
                                                                 dos_headers->e_lfanew);

    auto pattern_bytes = pattern_to_byte(moduleName);
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
