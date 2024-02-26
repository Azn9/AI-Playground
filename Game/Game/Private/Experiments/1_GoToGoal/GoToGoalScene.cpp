#include "Game/Public/Experiments/1_GoToGoal/GoToGoalScene.h"

#include <DirectXMath.h>

#include "AI/Public/Academy.h"
#include "Api/Public/Component/Basic/Physics/MeshCollider.h"
#include "Api/Public/Component/Basic/Physics/Rigidbody.h"
#include "Api/Public/GameObject/Basic/BasicCube.h"
#include "Game/Public/Experiments/1_GoToGoal/GoToGoalEnvironment.h"

using DirectX::XMFLOAT3;
using DirectX::XMVectorSet;

void GoToGoalScene::InitializePhysics()
{
    auto physicsResolver = std::make_unique<PM3D_API::PhysicsResolver>();
    physicsResolver->Initialize();
    SetPhysicsResolver(std::move(physicsResolver));
}

void GoToGoalScene::InitializeCamera()
{
    auto mainCamera = std::make_unique<PM3D_API::Camera>(
        "Main camera",
        PM3D_API::Camera::PERSPECTIVE,
        XMFLOAT3(0.f, 30.f, -30.f),
        XMVectorSet(0.f, 0.f, 0.f, 1.0f),
        XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
    );
    mainCamera->SetFieldOfView(45.0f);
    mainCamera->SetFarDist(200.0f);

    constexpr auto clearColor = XMFLOAT3(216.f / 255.f, 242.f / 255.f, 1.f);
    
    mainCamera->SetClearColor(clearColor);
    SetMainCamera(std::move(mainCamera));
}

void GoToGoalScene::InitializeLights()
{
    auto shadowProcessor = std::make_unique<ShadowProcessor>();
    shadowProcessor->Initialize();
    shadowProcessor->SetScene(this);
    AddComponent(std::move(shadowProcessor));
    
    auto directionalLight = std::make_unique<PM3D_API::DirectionalLight>(
        "Directional light",
        XMFLOAT3(1.0f, -1.0f, 0.0f)
    );
    directionalLight->SetIntensity(1.0f);
    directionalLight->Initialize();
    AddLight(std::move(directionalLight));
}

void GoToGoalScene::InitializeObjects()
{
    auto academy = std::make_unique<Academy>();
    const auto academyPtr = academy.get();
    AddComponent(std::move(academy));
    academyPtr->Initialize();
    
    auto environment = std::make_unique<GoToGoalEnvironment>(
        XMFLOAT3(0.0f, 0.0f, 0.0f)
    );
    const auto environmentPtr = environment.get();
    AddChild(std::move(environment));
    environmentPtr->Initialize();
}

void GoToGoalScene::InitializeUI()
{
    Scene::InitializeUI();
}

void GoToGoalScene::PostInitialize()
{
    Scene::PostInitialize();

    std::cout << "GoToGoalScene::PostInitialize()" << std::endl;
}

void GoToGoalScene::DrawSelf() const
{
    ImGui::Begin("Experiments - GoToGoal");

    

    ImGui::End();
}

