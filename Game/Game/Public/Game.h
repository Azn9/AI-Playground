#pragma once

#include "Api/Public/GameHost.h"

class Game final : public PM3D_API::GameHost
{
public:
    Game() = default;
    ~Game() override = default;

    void Initialize() override;
};
