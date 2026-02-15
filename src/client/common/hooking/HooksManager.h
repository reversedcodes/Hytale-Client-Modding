#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "IHooks.h"
#include "TFuncHook.h"

class HooksManager
{
public:
    template <class T, class... Args>
    T &Add(Args &&...args)
    {
        auto p = std::make_unique<T>(std::forward<Args>(args)...);
        T &ref = *p;
        m_all.emplace_back(std::move(p));
        return ref;
    }

    void InitAll()
    {
        MH_STATUS st = MH_Initialize();

        if (st != MH_OK && st != MH_ERROR_ALREADY_INITIALIZED)
        {
            std::cout << "HooksManager::InitAll MH_Initialize failed: " << TFuncHook::MHStatusToString(st) << "\n";
            return;
        }

        for (auto &x : m_all)
            x->Init();
    }
    void EnableAll()
    {
        for (auto &x : m_all)
            x->Enable();
    }
    
    void RestoreAll()
    {
        for (auto it = m_all.rbegin(); it != m_all.rend(); ++it)
            (*it)->Restore();

        MH_Uninitialize();
    }

    IHooks *GetHookByName(const std::string &name)
    {
        for (auto &x : m_all)
        {
            if (x->GetName() == name)
                return x.get();
        }
        return nullptr;
    }

    std::vector<std::unique_ptr<IHooks>> &GetAllHooks()
    {
        return m_all;
    }

private:
    std::vector<std::unique_ptr<IHooks>> m_all;
};
