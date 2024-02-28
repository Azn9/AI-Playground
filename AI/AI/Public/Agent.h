#pragma once
#include "Outputs.h"
#include "Api/Public/Component/Component.h"
#include "NN/FeedForwardNN.h"

class Trainer;
class Environment;
class Outputs;
class InputGatherer;

class Agent : public PM3D_API::Component
{
public:
    void Initialize() override;

    virtual void Setup(int& inputCount, int& outputCount) = 0;
    virtual void OnEpisodeBegin() = 0;
    virtual void OnEpisodeEnd() = 0;
    virtual void GatherInput(InputGatherer* inputGatherer) = 0;
    virtual void ComputeReward(float& reward) = 0;
    virtual void ApplyAction(Outputs* outputs) = 0;

    void Think();

    void SetId(const int id) { this->id = id; }
    void SetEnvironment(Environment* environment) { this->environment = environment; }
    void SetTrainer(Trainer* trainer) { this->trainer = trainer; }
    Trainer* GetTrainer() { return trainer; }

protected:
    Environment* environment = nullptr;
    Trainer* trainer = nullptr;
    InputGatherer* inputGatherer = nullptr;
    Outputs* outputs = nullptr;
    
    at::Tensor covMat;
    at::Tensor L;
    at::Tensor Lt;

private:
    int id = -1;

    // TODO: For now, we are using a simple feed forward neural network
    FeedForwardNN actionNetwork = nullptr;
    FeedForwardNN criticNetwork = nullptr;
};
