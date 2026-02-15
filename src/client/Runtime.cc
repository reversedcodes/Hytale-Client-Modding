#include "Runtime.h"

#include "client/common/utils/Terminal.h"
#include "client/core/Client.h"

#include "client/sdk/hook/hooks/GameMangerHook.h"
#include "client/sdk/hook/hooks/WindowHook.h"

void Runtime::Init(LPVOID hModule)
{
    Runtime::hModule = hModule;

    // Initialize and Register hooks
    m_HooksManager = std::make_unique<HooksManager>();
    m_HooksManager->Add<GameManagerHook>();
    m_HooksManager->Add<WindowHook>();

    m_HooksManager->InitAll();

    Client::GetInstance().Initialize(hModule);
}

void Runtime::Start()
{
    // Start the client and enable hooks
    Terminal::GetInstance().Open();
    m_HooksManager->EnableAll();
}

void Runtime::Shutdown()
{
    // Restore hooks and shutdown the client
    m_HooksManager->RestoreAll();
    Client::GetInstance().Shutdown();
    Terminal::GetInstance().Close();
}

void Runtime::Eject()
{
    // Request client shutdown and then unload the DLL
    Client::GetInstance().RequestShutdown();

    HANDLE hThread = CreateThread(nullptr, 0, [](LPVOID lpParam) -> DWORD {
        Runtime::GetInstance().Shutdown();
        Sleep(500);
        FreeLibraryAndExitThread((HMODULE)lpParam, 0); 
    }, hModule, 0, nullptr);

    if (hThread)
        CloseHandle(hThread);
}