#pragma once
#include "client/core/module/Module.h"
#include <Windows.h>
#include <imgui.h>

class ImGuiModule final : public Module
{
public:
    const char* GetName() const override { return "Gui"; }
    void OnEnable() override;
    void OnDisable() override;

    void _DrawGuiInterface();
    void _Initialize(HWND hWnd);
private:
    HWND m_hWnd = nullptr;
};
