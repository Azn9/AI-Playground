#pragma once
#include <vector>
#include "Api/Public/GameObject/GameObject.h"

class Outputs;
class InputGatherer;
class Agent;

class Environment : public PM3D_API::GameObject
{
public:
    Environment(const std::string& name)
        : GameObject(name)
    {
    }
    Environment(const std::string& name, const DirectX::XMFLOAT3& worldPosition)
        : GameObject(name, worldPosition)
    {
    }

    void Initialize() override;
    
    virtual void OnEpisodeBegin() = 0;
    virtual void OnEpisodeEnd() = 0;

    void Train();
    void RegisterAgent(Agent* agent);

    void BeginEpisode();
    void EndEpisode();

private:
    int nextAgentId = 0;
    std::vector<std::tuple<Agent*, std::tuple<InputGatherer*, Outputs*>>> agents;

    bool isEpisodeRunning = false;
};
