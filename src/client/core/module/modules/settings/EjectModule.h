#pragma once

#include "client/core/module/Module.h"

class EjectModule : public Module {
public:
    const char* GetName() const override  { return "Eject"; }
    void OnEnable() override;
    void OnDisable() override;
};