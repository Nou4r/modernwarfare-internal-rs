#pragma once

#include <dxgi1_4.h>
#include <cstdint>
#include <memory>

using PresentFunction = HRESULT (__fastcall*)(IDXGISwapChain3 *, UINT, UINT);

class Hooks
{
public:
    explicit Hooks();
    void hookWndProc();
    void hookPresent();
    void hookDiscord();
    void uninstall();

    WNDPROC originalWndProc{};
    PresentFunction originalPresent;
    HWND gameWindow;
private:
    HWND getProcessWindow();

    // https://github.com/hailzfn/IGodsEye-Reborn/blob/master/Hook/Hook.h#L43
    template<typename T>
    static inline T write(void *base, const int64_t index, T hook)
    {
        uintptr_t *vTable = *static_cast<uintptr_t**>(base);
        DWORD oldProtect = 0;
        VirtualProtect(&vTable[index], sizeof(uintptr_t), PAGE_READWRITE, &oldProtect);

        uintptr_t original = vTable[index];
        vTable[index] = reinterpret_cast<uintptr_t>(hook);

        VirtualProtect(&vTable[index], sizeof(uintptr_t), oldProtect, &oldProtect);

        return reinterpret_cast<T>(original);
    }
};

inline std::unique_ptr<Hooks> hooks;
