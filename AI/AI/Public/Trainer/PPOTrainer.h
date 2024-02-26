#pragma once
#include <vector>

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
    void Rollout();

private:
    int timestepsPerBatch;
    int epochs;
    int maxTimestepsPerEpisode;

    std::vector<float> batchObservations;
    std::vector<float> batchActions;
    std::vector<float> batchLogProbs;
    std::vector<float> batchRewards;
    std::vector<float> batchRewardToGo;
    std::vector<float> batchEpisodicLengths;
};
