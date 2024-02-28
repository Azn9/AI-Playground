#include "AI/Public/Trainer/PPOTrainer.h"

#include <stdexcept>
#include <torch/torch.h>

#include "AI/Public/Agent.h"
#include "AI/Public/Environment.h"

void PPOTrainer::Learn(int episodes)
{
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

void PPOTrainer::ComputeRewardsToGo()
{
    for (int i = batchRewards.size() - 1; i >= 0; --i)
    {
        float discountedReward = 0.0f;

        const auto reward = batchRewards[i];
        
    }
}

void PPOTrainer::Tick()
{
    if (!trainingRunning) return;

    currentTimestep++;

    agent->Think();

    if (currentTimestep >= timestepsPerBatch) // TODO: need to add another loop for the episodes
    {
        ComputeRewardsToGo();

        // Reset
        currentTimestep = 0;
        InitializeRollout();
    }
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
