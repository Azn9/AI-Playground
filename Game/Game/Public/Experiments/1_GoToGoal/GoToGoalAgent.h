#pragma once
#include "AI/Public/Agent.h"

class GoToGoalAgent : public Agent
{
protected:
    void Setup(int& inputCount, int& outputCount) override;
    void OnEpisodeBegin() override;
    void OnEpisodeEnd() override;
    void GatherInput(InputGatherer* inputGatherer) override;
    void ComputeReward(float& reward) override;
    void ApplyAction(Outputs* outputs) override;

};
