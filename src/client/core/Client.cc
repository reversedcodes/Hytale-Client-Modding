#include "Client.h"
#include <iostream>

#include "client/Runtime.h"

#include "client/core/module/modules/visual/ImGuiModule.h"
#include "client/core/module/modules/settings/EjectModule.h"
#include "client/core/module/modules/dev/ConsoleModule.h"


void Client::Initialize(HANDLE hModule)
{
    if (m_initialized)
        return;


    // Register modules
    m_ModuleManager.RegisterModule(std::make_unique<ImGuiModule>());
    m_ModuleManager.RegisterModule(std::make_unique<EjectModule>());
    m_ModuleManager.RegisterModule(std::make_unique<ConsoleModule>());
    m_ModuleManager.Initialize();

    m_hModule = hModule;
    m_initialized = true;
    m_running = true;
}

void Client::Shutdown()
{
    if (!m_initialized)
        return;

    m_ModuleManager.Shutdown();
    m_running = false;
    m_initialized = false;
}