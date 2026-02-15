#include "EjectModule.h"

#include "client/Runtime.h"

void EjectModule::OnEnable()
{
    this->Disable();
    Runtime::GetInstance().Eject();
}

void EjectModule::OnDisable()
{
    // No action needed on disable
}