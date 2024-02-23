#include "Game/Public/Scenes/EmptyScene.h"
#include <torch/torch.h>

void EmptyScene::Initialize()
{
    const auto tensor = torch::rand({2, 3});
    std::cout << tensor << std::endl;
}

void EmptyScene::InitializePhysics()
{
}

void EmptyScene::InitializeCamera()
{
}

void EmptyScene::InitializeLights()
{
}

void EmptyScene::InitializeObjects()
{
}

void EmptyScene::InitializeUI()
{
}
