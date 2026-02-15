#pragma once
#include <Windows.h>
#include <atomic>

#include "module/ModuleManager.h"

class Client
{
public:
    static Client &GetInstance()
    {
        static Client instance;
        return instance;
    }

    ModuleManager &GetModuleManager()
    {
        return m_ModuleManager;
    }


    void Initialize(HANDLE hModule);
    void Shutdown();

    bool IsInitialized() const { return m_initialized; }
    bool IsRunning() const { return m_running; }

    void RequestShutdown() { m_shutdownRequested = true; }
    bool ShutdownRequested() const { return m_shutdownRequested; }

private:
    Client() : m_ModuleManager() {}
    ~Client() = default;      
    Client(const Client &) = delete;
    Client &operator=(const Client &) = delete;
private:

    ModuleManager m_ModuleManager;

    HANDLE m_hModule = nullptr;
    bool m_initialized = false;
    bool m_running = false;
    std::atomic<bool> m_shutdownRequested = false;
};
