#pragma once

#include "client/common/hooking/HooksManager.h"

class Runtime
{
public:
    static Runtime &GetInstance()
    {
        static Runtime instance;
        return instance;
    }

    static void Init(LPVOID hModule);
    static void Start();
    static void Shutdown();
    static void Eject();

private:
    inline static LPVOID hModule = nullptr;
    inline static std::unique_ptr<HooksManager> m_HooksManager;
};
