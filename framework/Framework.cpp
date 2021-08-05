#include <Windows.h>
#include <cstdint>
#include "Framework.h"

#include "Debug.h"
#include "Graphics.h"
#include "Hooks.h"
#include "Memory.h"

Framework::Framework(HMODULE moduleHandle)
{
	memory = std::make_unique<Memory>();
	hooks = std::make_unique<Hooks>();
}

auto Framework::unload() -> void
{
	hooks->uninstall();
	Sleep(100);
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
}
