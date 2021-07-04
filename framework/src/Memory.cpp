//
// Created by draven on 6/6/2021.
//

#include "Memory.h"
#include "Debug.h"
#include "xorstr.h"

#include <Windows.h>

Memory::Memory() noexcept
{
    imageBase = reinterpret_cast<uint64_t>(GetModuleHandle(nullptr));
    peb = __readgsqword(0x60);
}

static HWND processHwnd;

static BOOL CALLBACK EnumWindowCallback(HWND hWnd, LPARAM lParam)
{
    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == lParam) {
        TCHAR classNameBuf[MAX_PATH];
        GetClassName(hWnd, classNameBuf, MAX_PATH);
        std::string className(&classNameBuf[0]);
        if (className != _("MSCTFIME UI") && className != _("IME") && className != _("ConsoleWindowClass")) {
            processHwnd = hWnd;
            return FALSE;
        }
    }
    return TRUE;
}

auto get_process_window() noexcept -> HWND
{
    if (processHwnd != nullptr) {
        return processHwnd;
    }

    EnumWindows(EnumWindowCallback, GetCurrentProcessId());

    if (processHwnd == nullptr) {
        DEBUG_ERROR("Could not find process window");
    }

    return processHwnd;
}
