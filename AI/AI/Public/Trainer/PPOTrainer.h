#pragma once
#include <vector>
#include <ATen/core/TensorBody.h>

#include "Trainer.h"

class PPOTrainer final : public Trainer
{
public:
    explicit PPOTrainer(
        Environment* environment,
        int timestepsPerBatch,
        int epochs,
        int maxTimestepsPerEpisode
    ) : Trainer(environment), timestepsPerBatch(timestepsPerBatch), epochs(epochs), maxTimestepsPerEpisode(maxTimestepsPerEpisode)
    {
    }

    void Learn(int episodes) override;
    void InitializeRollout();
    void Rollout();

    void Train();
    void AddReward(float reward) override;
    void AddActions(const at::Tensor& tensor, double log_prob) override;

private:
    int timestepsPerBatch;
    int epochs;
    int maxTimestepsPerEpisode;

    std::vector<at::Tensor> batchObservations;
    std::vector<at::Tensor> batchActions;
    std::vector<at::Tensor> batchLogProbs;
    std::vector<at::Tensor> batchRewards;
    std::vector<at::Tensor> batchRewardToGo;
    std::vector<at::Tensor> batchEpisodicLengths;

    bool trainingRunning = false;
    int currentTimestep = 0;
};
