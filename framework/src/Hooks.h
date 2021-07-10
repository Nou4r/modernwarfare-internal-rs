//
// Created by draven on 6/6/2021.
//
#pragma once

#include <memory>
#include <Windows.h>
#include <dxgi1_4.h>

using PresentFunction = HRESULT (__fastcall*)(IDXGISwapChain3 *, UINT, UINT);

class Hooks
{
public:
    explicit Hooks() noexcept;
    void hookWndProc() noexcept;
    void hookPresent() noexcept;
    void hookDiscord() noexcept;
    void uninstall() const noexcept;

    WNDPROC originalWndProc{};
    PresentFunction originalPresent;
private:
    // https://github.com/hailzfn/IGodsEye-Reborn/blob/master/Hook/Hook.h#L43
    template<typename T>
    static inline T write(void *base, int64_t index, T hook)
    {
        uintptr_t *vTable = *(uintptr_t **) base;
        DWORD oldProtect = 0;
        VirtualProtect(&vTable[index], sizeof(uintptr_t), PAGE_READWRITE, &oldProtect);

        uintptr_t original = vTable[index];
        vTable[index] = (uintptr_t) hook;

        VirtualProtect(&vTable[index], sizeof(uintptr_t), oldProtect, &oldProtect);

        return (T) original;
    }
};

inline std::unique_ptr<Hooks> hooks;