#include "Terminal.h"
#include <Windows.h>
#include <iostream>

void Terminal::Open()
{
    if (!AttachConsole(ATTACH_PARENT_PROCESS))
    {
        if (!AllocConsole())
        {
            return;
        }
    }

    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);

    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    SetConsoleTitleA("Hytale Client | Debug Terminal");
}

void Terminal::Close()
{
    FILE* fDummy;
    freopen_s(&fDummy, "NUL", "w", stdout);
    freopen_s(&fDummy, "NUL", "w", stderr);
    freopen_s(&fDummy, "NUL", "r", stdin);

    FreeConsole();
}