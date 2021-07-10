//
// Created by draven on 6/6/2021.
//

#include "Cheat.h"
#include "Memory.h"
#include "Hooks.h"
#include "Graphics.h"
#include "Debug.h"
#include "imgui_impl_dx12.h"
#include "interop.h"

Cheat::Cheat(HMODULE moduleHandle) noexcept
{
    this->moduleHandle = moduleHandle;
    memory = std::make_unique<Memory>();
    hooks = std::make_unique<Hooks>();

    on_load();
}

void Cheat::unload() noexcept
{
    hooks->uninstall();
    Sleep(100);

    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();

//    dbg::info("Unloaded");

//    FreeLibrary(moduleHandle);
}