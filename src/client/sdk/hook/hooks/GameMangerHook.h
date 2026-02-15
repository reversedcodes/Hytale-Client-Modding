#pragma once

#include "hytale/GameState.h"

#include "client/sdk/hook/HookBase.h"
#include "client/core/Client.h"

#include <iostream>

class GameManagerHook final : public HooksBase
{
public:
    std::string_view GetName() const override
    {
        return "GameStateHook";
    }

    void Init() override
    {
        CLIENT_CREATE_HOOK(m_ChangeGameStateHook, o_ChangeGameState, ChangeGameState, "41 56 57 56 55 53 48 83 EC 50 33 C0 48 89 44 24 48 48 89 44 24 40 48 8B D9 8B F2 48 8D 05", "GameStateHook::ChangeGameState");
    }

    void Enable() override
    {
        CLIENT_ENABLE_HOOK(m_ChangeGameStateHook, "GameStateHook::ChangeGameState");
    }

    void Restore() override
    {
        CLIENT_RESTORE_HOOK(m_ChangeGameStateHook);
    }

    static void ChangeGameState(void* a1, GameState state)
    {

        switch (state)
        {
        case GameState::Initial:
            std::cout << "GameState: Initial\n";
            break;
        case GameState::Startup:
            std::cout << "GameState: Startup\n";
            break;
        case GameState::MainMenu:
            std::cout << "GameState: MainMenu\n";
            Client::GetInstance().GetModuleManager().GetModule("Gui")->Disable();
            break;
        case GameState::GameLoading:
            std::cout << "GameState: GameLoading\n";
            Client::GetInstance().GetModuleManager().GetModule("Gui")->Disable();
            break;
        case GameState::InGame:
            std::cout << "GameState: InGame\n";
            Client::GetInstance().GetModuleManager().GetModule("Gui")->Enable();
            break;
        case GameState::Disconnection:
            std::cout << "GameState: Disconnection\n";
            Client::GetInstance().GetModuleManager().GetModule("Gui")->Disable();
            break;
        case GameState::Exited:
            std::cout << "GameState: Exited\n";
            break;
        case GameState::Unknown:
            std::cout << "GameState: Unknown\n";
            break;
        default:
            break;
        }

        o_ChangeGameState(a1, state);
    }

private:
    std::unique_ptr<TFuncHook> m_ChangeGameStateHook;
    static inline decltype(&ChangeGameState) o_ChangeGameState = nullptr;
};