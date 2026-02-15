#pragma once

/**
 * Template Hook class example. You can copy this and modify it to create new hooks.
 */

#include "client/sdk/hook/HookBase.h"

class ExampleHook final : public HooksBase
{
public:
    std::string_view GetName() const override
    {
        return "ExampleHook";
    }

    void Init() override
    {
        CLIENT_CREATE_HOOK(m_TestHook, o_TestHook,  TestHook, "41 56 31........ ", "ExampleHook::TestHook");
    }

    void Enable() override
    {
        CLIENT_ENABLE_HOOK(m_TestHook, "ExampleHook::TestHook");
    }

    void Restore() override
    {
        CLIENT_RESTORE_HOOK(m_TestHook);
    }

    static void TestHook(void* a1, void *a2)
    {

        o_TestHook(a1, a2);
    }

private:
    std::unique_ptr<TFuncHook> m_TestHook;
    static inline decltype(&TestHook) o_TestHook = nullptr;
};