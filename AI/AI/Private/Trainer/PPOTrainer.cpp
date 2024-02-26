#include "AI/Public/Trainer/PPOTrainer.h"

#include <stdexcept>

#include "AI/Public/Environment.h"

void PPOTrainer::Learn(int episodes)
{
    if (!environment)
    {
        throw std::runtime_error("PPOTrainer::Learn: environment is nullptr");
    }
    
    for (int i = 0; i < episodes; i++)
    {
        environment->BeginEpisode();

        

        environment->EndEpisode();
    }
}

void PPOTrainer::Rollout()
{
    
}