#pragma once
#include <vector>
#include <ATen/core/TensorBody.h>

#include "Trainer.h"

class Agent;

class PPOTrainer final : public Trainer
{
public:
    explicit PPOTrainer(
        Agent* agent,
        int timestepsPerBatch,
        int epochs,
        int maxTimestepsPerEpisode
    ) : Trainer(agent), timestepsPerBatch(timestepsPerBatch), epochs(epochs), maxTimestepsPerEpisode(maxTimestepsPerEpisode)
    {
    }

    void Learn(int episodes) override;
    void Tick() override;
    
    void InitializeRollout();
    void ComputeRewardsToGo();

    void AddReward(float reward) override;
    void AddActions(const at::Tensor& tensor, double log_prob) override;

private:
    int timestepsPerBatch;
    int epochs;
    int maxTimestepsPerEpisode;

    std::vector<at::Tensor> batchObservations;
    std::vector<at::Tensor> batchActions;
    std::vector<at::Tensor> batchLogProbs;
    std::vector<float> batchRewards;
    std::vector<std::vector<float>> episodeRewards;
    std::vector<at::Tensor> batchRewardToGo;
    std::vector<at::Tensor> batchEpisodicLengths;

    bool trainingRunning = false;
    int currentTimestep = 0;
};
