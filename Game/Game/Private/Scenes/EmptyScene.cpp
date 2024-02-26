#include "Game/Public/Scenes/EmptyScene.h"

#include "Api/Public/GameHost.h"
#include "Game/Public/Experiments/1_GoToGoal/GoToGoalScene.h"

void EmptyScene::Initialize()
{
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

void EmptyScene::DrawSelf() const
{
    ImGui::Begin("Experiments");

    Scene* scenePtr = nullptr;
    if (ImGui::Button("1- GoToGoal"))
    {
        scenePtr = GoToGoalScene::GetInstancePtr();
    }

    if (scenePtr)
    {
        scenePtr->Initialize();
        PM3D_API::GameHost::GetInstance()->SetScene(scenePtr);
    }

    ImGui::End();
}
