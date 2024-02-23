#include "Game/Public/Game.h"

#include "Game/Public/Scenes/EmptyScene.h"

PM3D_API::GameHost* PM3D_API::GameHost::GetInstance()
{
    static Game instance;
    return &instance;
}

void Game::Initialize()
{
    SetScene(EmptyScene::GetInstancePtr());
}
