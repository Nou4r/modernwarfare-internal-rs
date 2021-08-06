#include <string>
#include <d3d12.h>

#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

#include "Debug.h"
#include "Framework.h"
#include "Hooks.h"

#include "Graphics.h"
#include "Interop.h"
#include "Memory.h"
#include "Offsets.h"
#include "Util.h"
#include "xorstr.h"

__declspec(dllexport) HRESULT __fastcall hkPresent(IDXGISwapChain3* pSwapChain, UINT syncInterval, UINT flags)
{
    if (pSwapChain == nullptr) {
        return hooks->originalPresent(pSwapChain, syncInterval, flags);
    }

    const auto commandQueue = (ID3D12CommandQueue*) (readMemory<uintptr_t>(
            memory->imageBase + offsets::directx::command_queue));


    if (commandQueue == nullptr) {
        DEBUG_ERROR("Error in hooked present: commandQueue was null");
    }

    graphics::start(pSwapChain, commandQueue);
    graphics::newFrame();

    interop::on_frame(ImGui::GetCurrentContext());
    ImGui::ShowDemoWindow();

    const auto result = graphics::render(pSwapChain, syncInterval, flags);
    return result;
}

__declspec(dllexport) LRESULT hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();
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
            if (io.WantCaptureMouse) {
                return ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
            } else {
                return CallWindowProc(hooks->originalWndProc, hWnd, uMsg, wParam, lParam);
            }
        }
        case WM_KEYDOWN: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyDown), wParam);
            break;
        }
        case WM_KEYUP: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyUp), wParam);
            break;
        }

        case WM_LBUTTONDOWN: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyDown), VK_LBUTTON);
            break;
        }
        case WM_LBUTTONUP: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyUp), VK_LBUTTON);
            break;
        }

        case WM_RBUTTONDOWN: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyDown), VK_RBUTTON);
            break;
        }
        case WM_RBUTTONUP: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyUp), VK_RBUTTON);
            break;
        }

        case WM_MBUTTONDOWN: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyDown), VK_MBUTTON);
            break;
        }
        case WM_MBUTTONUP: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyUp), VK_MBUTTON);
            break;
        }

        case WM_XBUTTONDOWN: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyDown),
	                                (GET_XBUTTON_WPARAM(wParam) == 1) ? VK_XBUTTON1 : VK_XBUTTON2);
            break;
        }
        case WM_XBUTTONUP: {
	        interop::on_input_event(static_cast<int32_t>(InputEventType::KeyUp),
	                                (GET_XBUTTON_WPARAM(wParam) == 1) ? VK_XBUTTON1 : VK_XBUTTON2);
            break;
        }
    };

    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
    if (io.WantCaptureMouse &&
        (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP ||
         uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEMOVE ||
         uMsg == WM_MOUSEHOVER || uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)) {
        return TRUE;
    }
    if (io.WantCaptureKeyboard && (
            uMsg == WM_KEYDOWN || uMsg == WM_KEYUP
    )) {
        return TRUE;
    }

    return CallWindowProc(hooks->originalWndProc, hWnd, uMsg, wParam, lParam);
}


Hooks::Hooks()
{
    this->gameWindow = getProcessWindow();
    hookPresent();
}

void Hooks::hookWndProc()
{
    originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(gameWindow, GWLP_WNDPROC,
                                                                  reinterpret_cast<LONG_PTR>(hkWndProc)));
}

void Hooks::hookPresent()
{
    // Hook present
    const auto swapChainBase = readMemory<uint64_t>(memory->imageBase + offsets::directx::swap_chain);

    if (swapChainBase == 0) {
        DEBUG_ERROR("Error installing present hook: swap chain base address was 0");
        return;
    }

    originalPresent = Hooks::write((void*) swapChainBase, 8, hkPresent);
}

void Hooks::hookDiscord()
{
    const auto pCallPresentDiscord = utils::findPattern("DiscordHook64.dll",
                                                        "41 89 F0 FF 15 ? ? ? ? 89 C6 E8 ? ? ? ?");

    if (!pCallPresentDiscord) {
        DEBUG_ERROR("Could not find discord present");
        return;
    }

    const auto pOriginalPresent = reinterpret_cast< PresentFunction* >( pCallPresentDiscord +
                                                                        *reinterpret_cast< int32_t* >(pCallPresentDiscord + 0x5 ) + 0x9 );

    if (!*pOriginalPresent) {
        DEBUG_ERROR("Could not deref discord present");
        return;
    }

    originalPresent = *pOriginalPresent;
    *pOriginalPresent = hkPresent;
}

void Hooks::uninstall()
{
    // Unhook present
    const auto swapChainBase = *reinterpret_cast<std::uint64_t*>(memory->imageBase + offsets::directx::swap_chain);

    if (swapChainBase == 0) {
        DEBUG_ERROR("Error uninstalling present hook: swap chain base address was 0");
    }
    Hooks::write((void*) swapChainBase, 8, originalPresent);

    // TODO: Unhook wndproc (maybe not necessary)
    SetWindowLongPtrW(gameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWndProc));
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

HWND Hooks::getProcessWindow()
{
    EnumWindows(EnumWindowCallback, GetCurrentProcessId());

    if (processHwnd == nullptr) {
        DEBUG_ERROR("Could not find process window");
    }

    return processHwnd;
}
