//
// Created by draven on 6/6/2021.
//

#define DEBUG
#define DEBUG_READ

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <memory>

#include "Debug.h"
#include "Cheat.h"

BOOL APIENTRY DllMain(HMODULE moduleHandle, DWORD reason, LPVOID reserved)
{
    if (reason != DLL_PROCESS_ATTACH) {
        return TRUE;
    }

#ifdef DEBUG
//    AllocConsole();
//    freopen("CONOUT$", "w", stdout);
#endif

    dbg::info("Loaded");

    cheat = std::make_unique<Cheat>(moduleHandle);

    return TRUE;
}