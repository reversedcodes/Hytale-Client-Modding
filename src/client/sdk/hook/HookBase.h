#pragma once

#include "client/common/hooking/HooksBase.h"
#include "client/common/utils/Memory.h"

namespace client::detail
{
    template <class T, class = void>
    struct OptionalLike : std::false_type
    {
    };

    template <class T>
    struct OptionalLike<T, std::void_t<decltype(static_cast<bool>(std::declval<T &>())), decltype(std::declval<T &>().value())>> : std::true_type
    {
    };

    template <class T>
    static inline std::uintptr_t ToAddr(const T &v)
    {
        if constexpr (OptionalLike<T>::value)
        {
            return ToAddr(v.value());
        }
        else if constexpr (std::is_pointer_v<T>)
        {
            return reinterpret_cast<std::uintptr_t>(v);
        }
        else
        {
            return static_cast<std::uintptr_t>(v);
        }
    }
}

#define CLIENT_CREATE_HOOK(memberHook, origFnPtr, detourFn, pattern, fullName)        \
    do                                                                                \
    {                                                                                 \
        try                                                                           \
        {                                                                             \
            auto _target = Memory::FindPattern((pattern));                            \
            if (!_target)                                                             \
            {                                                                         \
                throw std::runtime_error(                                             \
                    std::string("Failed to find pattern for hook creation. NAME: ") + \
                    std::string((fullName)) +                                         \
                    " SIGNATURE: " + std::string((pattern)));                         \
            }                                                                         \
            std::uintptr_t _addr = ::client::detail::ToAddr(_target);                 \
            (memberHook) = CreateFuncOne(_addr, (void *)&(detourFn), (fullName));     \
            (origFnPtr) = Orig<decltype(&(detourFn))>((memberHook));                  \
        }                                                                             \
        catch (const std::exception &e)                                               \
        {                                                                             \
            throw std::runtime_error(std::string("CLIENT_CREATE_HOOK failed [") +      \
                                     std::string((fullName)) + "]: " + e.what());     \
        }                                                                             \
    } while (0)

#define CLIENT_CREATE_HOOK_MODULE(memberHook, origFnPtr, moduleName, exportName, detourFn, fullName)      \
    do                                                                                                    \
    {                                                                                                     \
        try                                                                                               \
        {                                                                                                 \
            auto _mod = ProcessHelper::getModuleBaseLoad((moduleName));                                   \
            if (!_mod)                                                                                    \
            {                                                                                             \
                throw std::runtime_error(std::string("Module not loaded: ") + std::string((moduleName))); \
            }                                                                                             \
                                                                                                          \
            auto _target = ProcessHelper::getExport(_mod, (exportName));                                  \
            if (!_target)                                                                                 \
            {                                                                                             \
                throw std::runtime_error(std::string("Export not found: ") +                              \
                                         std::string((exportName)) + " in " + std::string((moduleName))); \
            }                                                                                             \
                                                                                                          \
            std::uintptr_t _addr = ::client::detail::ToAddr(_target);                                      \
            (memberHook) = CreateFuncOne(_addr, (void *)&(detourFn), (fullName));                         \
            (origFnPtr) = Orig<decltype(&(detourFn))>((memberHook));                                      \
        }                                                                                                 \
        catch (const std::exception &e)                                                                   \
        {                                                                                                 \
            throw std::runtime_error(std::string("CLIENT_CREATE_HOOK_MODULE failed [") +                  \
                                     std::string((fullName)) + "]: " + e.what());                         \
        }                                                                                                 \
    } while (0)

#define CLIENT_ENABLE_HOOK(memberHook, fullName) \
    do                                           \
    {                                            \
        EnableOne((memberHook), (fullName));     \
    } while (0)

#define CLIENT_RESTORE_HOOK(memberHook) \
    do                                  \
    {                                   \
        RestoreOne((memberHook));       \
    } while (0)
