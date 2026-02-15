#pragma once
#include <cstdint>
#include "NetworkType.h"

enum class GameState : int32_t {
    Initial      = 0,
    Startup      = 1,
    MainMenu     = 2,
    GameLoading  = 3,
    InGame       = 4,
    Disconnection = 5,
    Exited       = 6,
    Unknown      = -1 
};