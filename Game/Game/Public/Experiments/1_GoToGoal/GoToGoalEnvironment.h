#pragma once
#include "AI/Public/Environment.h"
#include "Api/Public/GameObject/GameObject.h"

class GoToGoalEnvironment final : public Environment
{
public:
    explicit GoToGoalEnvironment(const DirectX::XMFLOAT3 worldPosition)
        : Environment("GoToGoalEnvironment", worldPosition)
    {
    }
    void Initialize() override;
    void OnEpisodeBegin() override;
    void OnEpisodeEnd() override;

private:
    void InitializeGround();
    void InitializeTarget();
    void InitializeAgent();
};
