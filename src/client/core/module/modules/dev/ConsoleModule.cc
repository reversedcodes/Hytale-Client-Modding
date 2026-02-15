#include "ConsoleModule.h"
#include "client/common/utils/Terminal.h"

void ConsoleModule::OnEnable()
{
    Terminal::GetInstance().Open();
}

void ConsoleModule::OnDisable()
{
    Terminal::GetInstance().Close();
}

void ConsoleModule::OnShutdown()
{
    this->OnDisable();
}