#include <iostream>
#include <thread>
#include "Runtime.h"

static DWORD WINAPI init(LPVOID hModule)
{
    Runtime::GetInstance().Init(hModule);
    Runtime::GetInstance().Start();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, init, hModule, 0, nullptr);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        Runtime::GetInstance().Shutdown();
    }
    return TRUE;
}