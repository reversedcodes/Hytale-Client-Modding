#pragma once
#include "Module.h"

#include <vector>
#include <memory>
#include <string_view>

class ModuleManager
{
public:
    ModuleManager() = default;
    ~ModuleManager() = default;

    ModuleManager(const ModuleManager &) = delete;
    ModuleManager &operator=(const ModuleManager &) = delete;

    void Initialize()
    {
        for (auto &m : m_modules)
            m->OnInitialize();
    }

    void Shutdown()
    {
        for (auto &m : m_modules)
            m->OnShutdown();
        m_modules.clear();
    }

    void Update()
    {
        for (auto &m : m_modules)
            if (m->IsEnabled())
                m->OnUpdate();
    }
    
    void RegisterModule(std::unique_ptr<Module> module)
    {
        m_modules.emplace_back(std::move(module));
    }

    std::unique_ptr<Module> UnregisterModule(std::string_view name)
    {
        for (size_t i = 0; i < m_modules.size(); i++)
        {
            if (name == m_modules[i]->GetName())
            {
                auto out = std::move(m_modules[i]);
                m_modules.erase(m_modules.begin() + i);
                return out;
            }
        }
        return {};
    }

    Module *GetModule(std::string_view name)
    {
        for (auto &m : m_modules)
            if (name == m->GetName())
                return m.get();
        return nullptr;
    }

    const std::vector<std::unique_ptr<Module>> &GetModules() const { return m_modules; }

    bool Enable(std::string_view name)
    {
        if (auto *m = GetModule(name))
        {
            m->Enable();
            return true;
        }
        return false;
    }

    bool Disable(std::string_view name)
    {
        if (auto *m = GetModule(name))
        {
            m->Disable();
            return true;
        }
        return false;
    }

    bool Toggle(std::string_view name)
    {
        if (auto *m = GetModule(name))
        {
            m->IsEnabled() ? m->Disable() : m->Enable();
            return true;
        }
        return false;
    }

private:
    std::vector<std::unique_ptr<Module>> m_modules;
};
