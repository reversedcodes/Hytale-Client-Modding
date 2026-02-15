#include "ImGuiModule.h"
#include "client/core/Client.h"
#include "client/Runtime.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>
#include <imgui.h>

void ImGuiModule::OnEnable()
{

}

void ImGuiModule::OnDisable()
{
    if (ImGui::GetCurrentContext())
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
}

void ImGuiModule::_Initialize(HWND hWnd)
{
    m_hWnd = hWnd;
    if (ImGui::GetCurrentContext()) return;

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplOpenGL3_Init("#version 130");    
}


void ImGuiModule::_DrawGuiInterface()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Hytale Client"))
    {
        ImGui::Text("Hello, Hytale Client!");
    }

    if(ImGui::Button("Open Console"))
    {
        Client::GetInstance().GetModuleManager().GetModule("Console")->Toggle();
    }

    if(ImGui::Button("Eject"))
    {
        Runtime::GetInstance().Eject();        
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}