#pragma once
#include <memory>
#include <iostream>
#include <exception>
#include <cstdint>

#include "IHooks.h"
#include "TFuncHook.h"


class HooksBase : public IHooks
{
protected:
    static std::unique_ptr<TFuncHook> CreateFuncOne(std::uintptr_t adress, void *detour, const char *name)
    {
        try
        {
            void *target = reinterpret_cast<void *>(adress);
            return std::make_unique<TFuncHook>(target, detour);
        }
        catch (const std::exception &e)
        {
            std::cout << "Hook create failed [" << name << "]: " << e.what() << "\n";
            return nullptr;
        }
    }

    static void EnableOne(std::unique_ptr<TFuncHook> &h, const char *name)
    {
        if (!h)
            return;
        try
        {
            h->Enable();
        }
        catch (const std::exception &e)
        {
            std::cout << "Hook enable failed [" << name << "]: " << e.what() << "\n";
        }
    }

    static void RestoreOne(std::unique_ptr<TFuncHook> &h)
    {
        if (h)
            h->Restore();
    }

    template <typename Fn>
    static Fn Orig(std::unique_ptr<TFuncHook> &h)
    {
        return h ? h->OriginalAs<Fn>() : nullptr;
    }
};
