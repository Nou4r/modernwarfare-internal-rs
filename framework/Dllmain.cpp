// dllmain.cpp : Defines the entry point for the DLL application.
#include <memory>
#include <Windows.h>

#include "Debug.h"
#include "Framework.h"
#include "Interop.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  reason,
                       LPVOID lpReserved
)
{
    if(reason != DLL_PROCESS_ATTACH)
    {
        return TRUE;
    }

    interop::on_load();
    framework = std::make_unique<Framework>(hModule);

    return TRUE;
}

