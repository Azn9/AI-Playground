#include "Game/Public/Experiments/1_GoToGoal/GoToGoalEnvironment.h"
#include "Game/Public/Experiments/1_GoToGoal/GoToGoalAgent.h"

#include "Api/Public/Component/Basic/Physics/BoxCollider.h"
#include "Api/Public/Component/Basic/Physics/Rigidbody.h"
#include "Api/Public/GameObject/Basic/BasicCube.h"

void GoToGoalEnvironment::Initialize()
{
    InitializeGround();
    InitializeTarget();
    InitializeAgent();
}

void GoToGoalEnvironment::OnEpisodeBegin()
{
    // TODO : Random position for the target
    // TODO : Random position for the agent
}

void GoToGoalEnvironment::OnEpisodeEnd()
{
    
}

void GoToGoalEnvironment::InitializeGround()
{
    auto ground = std::make_unique<PM3D_API::BasicCube>(
        "Ground",
        XMFLOAT3(0.0f, -1.0f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT3(10.0f, 0.1f, 10.0f)
    );
    const auto groundPtr = ground.get();
    AddChild(std::move(ground));
    groundPtr->Initialize();

    groundPtr->GetComponent<PM3D_API::MeshRenderer>()->SetCustomColor(XMFLOAT3(0.f, 0.f, 0.f));

    auto groundRigidbody = std::make_unique<PM3D_API::Rigidbody>(true);
    const auto groundRigidbodyPtr = groundRigidbody.get();
    groundPtr->AddComponent(std::move(groundRigidbody));
    groundRigidbodyPtr->Initialize();
    
    auto groundCollider = std::make_unique<PM3D_API::BoxCollider>(scene->GetPhysicsResolver()->GetDefaultMaterial());
    const auto groundColliderPtr = groundCollider.get();
    groundPtr->AddComponent(std::move(groundCollider));
    groundColliderPtr->Initialize();
}

void GoToGoalEnvironment::InitializeTarget()
{
    auto target = std::make_unique<PM3D_API::BasicCube>(
        "Target",
        XMFLOAT3(5.0f, 1.0f, 5.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT3(0.5f, 0.5f, 0.5f)
    );
    const auto targetPtr = target.get();
    AddChild(std::move(target));
    targetPtr->Initialize();

    targetPtr->GetComponent<PM3D_API::MeshRenderer>()->SetCustomColor(XMFLOAT3(255.f, 255.f, 0.f));
}

void GoToGoalEnvironment::InitializeAgent()
{
    auto agent = std::make_unique<PM3D_API::BasicCube>(
        "Agent",
        XMFLOAT3(0.0f, 5.0f, 0.0f),
        XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT3(1.f, 1.f, 1.f)
    );
    const auto agentPtr = agent.get();
    AddChild(std::move(agent));
    agentPtr->Initialize();

    auto agentRigidbody = std::make_unique<PM3D_API::Rigidbody>(true);
    const auto agentRigidbodyPtr = agentRigidbody.get();
    agentPtr->AddComponent(std::move(agentRigidbody));
    agentRigidbodyPtr->Initialize();
    
    auto agentCollider = std::make_unique<PM3D_API::BoxCollider>(scene->GetPhysicsResolver()->GetDefaultMaterial());
    const auto agentColliderPtr = agentCollider.get();
    agentPtr->AddComponent(std::move(agentCollider));
    agentColliderPtr->Initialize();

    auto agentComponent = std::make_unique<GoToGoalAgent>();
    agentComponent->SetEnvironment(this);
    agentPtr->AddComponent(std::move(agentComponent));
}
