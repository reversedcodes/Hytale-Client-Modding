#pragma once

#include <MinHook.h>

#include <stdexcept>
#include <string>

class TFuncHook
{
public:
    void *funcTarget = nullptr;
    void *funcReal = nullptr;

    TFuncHook() = default;

    TFuncHook(void *target, void *detour)
    {
        Init(target, detour);
    }

    ~TFuncHook()
    {
        Restore();
    }

    TFuncHook(const TFuncHook &) = delete;
    TFuncHook &operator=(const TFuncHook &) = delete;

    static std::string MHStatusToString(MH_STATUS status)
    {
        switch (status)
        {
        case MH_UNKNOWN:
            return "Unknown error";
        case MH_OK:
            return "OK";
        case MH_ERROR_ALREADY_INITIALIZED:
            return "Already initialized";
        case MH_ERROR_NOT_INITIALIZED:
            return "Not initialized";
        case MH_ERROR_ALREADY_CREATED:
            return "Already created";
        case MH_ERROR_NOT_CREATED:
            return "Not created";
        case MH_ERROR_ENABLED:
            return "Already enabled";
        case MH_ERROR_DISABLED:
            return "Already disabled";
        case MH_ERROR_NOT_EXECUTABLE:
            return "Not executable";
        case MH_ERROR_UNSUPPORTED_FUNCTION:
            return "Unsupported function";
        case MH_ERROR_MEMORY_ALLOC:
            return "Memory allocation failed";
        case MH_ERROR_MEMORY_PROTECT:
            return "Memory protection failed";
        case MH_ERROR_MODULE_NOT_FOUND:
            return "Module not found";
        case MH_ERROR_FUNCTION_NOT_FOUND:
            return "Function not found";
        default:
            return "Unknown status code (" + std::to_string(status) + ")";
        }
    }

    void Enable()
    {
        if (!funcTarget)
            return;
        if (m_installed)
            return;

        MH_STATUS st = MH_EnableHook(funcTarget);

        if (st != MH_OK)
            throw std::runtime_error("TFuncHook::Enable failed: " + MHStatusToString(st));

        m_installed = true;
    }

    void Disable()
    {
        if (m_installed)
        {
            MH_STATUS st = MH_DisableHook(funcTarget);
            if (st != MH_OK && st != MH_ERROR_DISABLED)
                throw std::runtime_error("TFuncHook::Disable failed: " + MHStatusToString(st));

            m_installed = false;
        }
    }

    void Restore()
    {
        if (!funcTarget)
            return;

        Disable();

        MH_STATUS st = MH_RemoveHook(funcTarget);

        if (st != MH_OK && st != MH_ERROR_NOT_CREATED)
            throw std::runtime_error("TFuncHook::Restore (MH_RemoveHook) failed: " + MHStatusToString(st));

        funcTarget = nullptr;
        funcReal = nullptr;
    }
    template <typename Fn>
    Fn OriginalAs() const
    {
        return reinterpret_cast<Fn>(funcReal);
    }

    template <typename TRet, typename... TArgs>
    TRet CallOriginal(TArgs... args)
    {
        using FnType = TRet (*)(TArgs...);
        auto fn = reinterpret_cast<FnType>(funcReal);
        return fn(args...);
    }

private:
    void Init(void *target, void *detour)
    {
        funcTarget = target;
        m_detour = detour;

        MH_STATUS st = MH_CreateHook(funcTarget, m_detour, &funcReal);

        if (st != MH_OK)
        {
            funcTarget = nullptr;
            throw std::runtime_error("TFuncHook::Init (MH_CreateHook) failed: " + MHStatusToString(st));
        }
    }

private:
    void *m_detour = nullptr;
    bool m_installed = false;
};