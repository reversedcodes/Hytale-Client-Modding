#pragma once
#include "client/sdk/hook/HookBase.h"
#include "client/core/Client.h"
#include "client/core/module/modules/visual/ImGuiModule.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WindowHook final : public HooksBase
{
public:
    std::string_view GetName() const override { return "WindowHook"; }

    void Init() override
    {
        CLIENT_CREATE_HOOK_MODULE(m_SwapBuffersHook, o_SwapBuffers, "opengl32.dll", "wglSwapBuffers", wglSwapBuffers, "WindowHook::wglSwapBuffers");
    }

    void Enable() override
    {
        CLIENT_ENABLE_HOOK(m_SwapBuffersHook, "WindowHook::wglSwapBuffers");
    }

    void Restore() override
    {
        CLIENT_RESTORE_HOOK(m_SwapBuffersHook);

        if (m_hWnd && o_WndProc)
            SetWindowLongPtrW(m_hWnd, GWLP_WNDPROC, (LONG_PTR)o_WndProc);

        m_hWnd = nullptr;
        o_WndProc = nullptr;
        m_hwndInitialized = false;
    }

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (Client::GetInstance().IsRunning())
        {
            auto module = Client::GetInstance().GetModuleManager().GetModule("Gui");

            if (module && module->IsEnabled())
            {
                if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
                    return true;
            }
        }
        return CallWindowProcW(o_WndProc, hWnd, msg, wParam, lParam);
    }

    static BOOL WINAPI wglSwapBuffers(HDC hdc)
    {
        if (!m_hwndInitialized)
        {
            m_hWnd = WindowFromDC(hdc);

            if (m_hWnd)
                m_hwndInitialized = true;
        }

        if (m_hwndInitialized && !o_WndProc)
        {
            o_WndProc = (WNDPROC)SetWindowLongPtrW(m_hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
        }

        if (Client::GetInstance().IsRunning())
        {
            auto module = Client::GetInstance().GetModuleManager().GetModule("Gui");
            auto guiModule = static_cast<ImGuiModule *>(module);

            if (guiModule && guiModule->IsEnabled())
            {
                guiModule->_Initialize(m_hWnd);
                
                if (ImGui::GetCurrentContext())
                {
                    guiModule->_DrawGuiInterface();
                }
            }
        }
        return o_SwapBuffers(hdc);
    }

public:
    static inline HWND m_hWnd = nullptr;
    static inline bool m_hwndInitialized = false;
    static inline WNDPROC o_WndProc = nullptr;

private:
    std::unique_ptr<TFuncHook> m_SwapBuffersHook;
    static inline decltype(&wglSwapBuffers) o_SwapBuffers = nullptr;
};