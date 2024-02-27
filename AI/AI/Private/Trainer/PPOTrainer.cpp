#include "AI/Public/Trainer/PPOTrainer.h"

#include <stdexcept>
#include <torch/torch.h>

#include "AI/Public/Environment.h"

void PPOTrainer::Learn(int episodes)
{
    if (!environment)
    {
        throw std::runtime_error("PPOTrainer::Learn: environment is nullptr");
    }

    if (trainingRunning)
    {
        return;
    }
    trainingRunning = true;

    currentTimestep = 0;
}

void PPOTrainer::InitializeRollout()
{
    batchObservations.clear();
    batchActions.clear();
    batchLogProbs.clear();
    batchRewards.clear();
    batchRewardToGo.clear();
    batchEpisodicLengths.clear();

    batchObservations.resize(timestepsPerBatch);
    batchActions.resize(timestepsPerBatch);
    batchLogProbs.resize(timestepsPerBatch);
    batchRewards.resize(timestepsPerBatch);
    batchRewardToGo.resize(timestepsPerBatch);

    //batchEpisodicLengths.resize(??);
}

void PPOTrainer::Rollout()
{
    
}

void PPOTrainer::Train()
{
    if (!trainingRunning) return;

    
}

void PPOTrainer::AddReward(float reward)
{
    batchRewards[currentTimestep] = at::Tensor().new_ones({1, 1}).mul(reward).to(torch::kCUDA);
}

void PPOTrainer::AddActions(const at::Tensor& tensor, double log_prob)
{
    batchActions[currentTimestep] = tensor.to(torch::kCUDA);
    batchLogProbs[currentTimestep] = at::Tensor().new_ones({1, 1}).mul(log_prob).to(torch::kCUDA);
}
