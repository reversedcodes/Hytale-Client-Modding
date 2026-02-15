#pragma once

#include "client/core/module/Module.h"

class ConsoleModule final : public Module
{
    const char *GetName() const override { return "Console"; }
    void OnEnable() override;
    void OnDisable() override;
    void OnShutdown() override;
};