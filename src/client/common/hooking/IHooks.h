#pragma once
#include <string_view>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "client/common/utils/Memory.h"

struct IHooks
{
    virtual ~IHooks() = default;
    virtual std::string_view GetName() const = 0;
    virtual void Init() = 0;
    virtual void Enable() = 0;
    virtual void Restore() = 0;
};