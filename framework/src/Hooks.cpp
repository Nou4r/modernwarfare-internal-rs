//
// Created by draven on 6/6/2021.
//

#include "Hooks.h"
#include "Offsets.h"
#include "Memory.h"
#include "Debug.h"
#include "Graphics.h"
#include "Cheat.h"
#include "interop.h"

#include <d3d12.h>
#include <chrono>

static HRESULT __fastcall hkPresent(IDXGISwapChain3* pSwapChain, UINT syncInterval, UINT flags)
{
    if (pSwapChain == nullptr) {
        return hooks->originalPresent(pSwapChain, syncInterval, flags);
    }

    const auto commandQueue = (ID3D12CommandQueue*) (readMemory<uintptr_t>(
            memory->imageBase + offsets::directx::command_queue));


    if (commandQueue == nullptr) {
        dbg::error(_("Error in hooked present: commandQueue was null"));
    }

    const auto start = std::chrono::high_resolution_clock::now();

    graphics::start(pSwapChain, commandQueue);
    graphics::newFrame();

    on_frame(ImGui::GetCurrentContext());
//    ImGui::ShowDemoWindow();

    const auto result = graphics::render(pSwapChain, syncInterval, flags);

    const auto end = std::chrono::high_resolution_clock::now();
    cheat->tickTime = end - start;
    return result;
}

static LRESULT hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case 0x403:
        case WM_SIZE: {
            if (uMsg == WM_SIZE && wParam == SIZE_MINIMIZED)
                break;

            if (graphics::started) {
                graphics::clear();
                ImGui_ImplDX12_InvalidateDeviceObjects();
                graphics::needsRestart = true;
            }
            break;
        }
        case WM_SETCURSOR: {
            if (hooks->captureMouse) {
                return ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
            } else {
                return CallWindowProc(hooks->originalWndProc, hWnd, uMsg, wParam, lParam);
            }
        }
            // TODO: Add mouse events
        case WM_KEYDOWN: {
            cheat->handleInputEvent(InputEventType::KeyDown, wParam);
            break;
        }
        case WM_KEYUP: {
            cheat->handleInputEvent(InputEventType::KeyUp, wParam);
            break;
        }
    };

    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
    if (hooks->captureMouse &&
        (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP ||
         uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEMOVE ||
         uMsg == WM_MOUSEHOVER || uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)) {
        return TRUE;
    }

    return CallWindowProc(hooks->originalWndProc, hWnd, uMsg, wParam, lParam);
}

Hooks::Hooks() noexcept
{
    // Hook present
    const auto swapChainBase = *reinterpret_cast<std::uint64_t*>(memory->imageBase + offsets::directx::swap_chain);

    if (swapChainBase == 0) {
        DEBUG_ERROR("Error installing present hook: swap chain base address was 0");
        return;
    }

    originalPresent = Hooks::write((void*) swapChainBase, 8, hkPresent);
}

void Hooks::hookWndProc() noexcept
{
    originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(get_process_window(), GWLP_WNDPROC,
                                                                  (LONG_PTR) hkWndProc));
}

void Hooks::uninstall() const noexcept
{
    // Unhook present
    const auto swapChainBase = *reinterpret_cast<std::uint64_t*>(memory->imageBase + offsets::directx::swap_chain);

    if (swapChainBase == 0) {
        DEBUG_ERROR("Error uninstalling present hook: swap chain base address was 0");
    }
    Hooks::write((void*) swapChainBase, 8, originalPresent);

    // TODO: Unhook wndproc (maybe not necessary)
    SetWindowLongPtrW(get_process_window(), GWLP_WNDPROC, (LONG_PTR) originalWndProc);
}
