#pragma once

#include <windows.h>

class Module
{
public:
    virtual ~Module() = default;

    virtual const char *GetName() const = 0;
    virtual void OnInitialize() {}
    virtual void OnEnable() {}
    virtual void OnDisable() {}
    virtual void OnShutdown() {}

    virtual void OnUpdate() {}

    bool IsEnabled() const { return m_enabled; }

    void Enable()
    {
        if (!m_enabled)
        {
            OnEnable();
            m_enabled = true;
        }
    }
    void Disable()
    {
        if (m_enabled)
        {
            OnDisable();
            m_enabled = false;
        }
    }

    void Toggle()
    {
        if (m_enabled)
        {
            Disable();
        }
        else
        {
            Enable();
        }
    }

private:
    bool m_enabled = false;
};
