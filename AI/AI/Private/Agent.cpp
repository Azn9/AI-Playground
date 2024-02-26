#include "AI/Public/Agent.h"

#include <iostream>
#include <ostream>

#include "AI/Public/Environment.h"

#include <stdexcept>
#include "Api/Public/GameObject/GameObject.h"

void Agent::Initialize()
{
    if (!parentObject)
    {
        throw std::runtime_error("Agent::Initialize: parentObject is nullptr");
    }

    if (!environment)
    {
        throw std::runtime_error("Agent::Initialize: environment is nullptr");
    }

    environment->RegisterAgent(this);
}

void Agent::Initialize(int inputs, int outputs)
{
    // Create NN
    actionNetwork = FeedForwardNN(inputs, outputs);
    criticNetwork = FeedForwardNN(inputs, 1);
}

void Agent::Think(InputGatherer* inputGatherer, Outputs* outputs)
{
    
}

void Agent::ProcessReward(const float reward)
{
    
}

