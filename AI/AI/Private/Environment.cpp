﻿#include "AI/Public/Environment.h"

#include <iostream>

#include "AI/Public/Academy.h"
#include "AI/Public/Agent.h"
#include "AI/Public/InputGatherer.h"
#include "AI/Public/Outputs.h"
#include "AI/Public/Trainer/Trainer.h"
#include "Api/Public/GameObject/GameObject.h"
#include "Api/Public/Scene/Scene.h"

void Environment::Initialize()
{
    const auto parentObject = GetParent();
    if (!parentObject)
    {
        throw std::runtime_error("Environment::Initialize: parentObject is nullptr");
    }

    const auto academy = parentObject->GetScene()->GetComponent<Academy>();
    academy->RegisterEnvironment(this);
}

void Environment::Tick()
{
    for (auto [agent, inout] : agents)
    {
        const auto trainer = agent->GetTrainer();
        if (trainer)
        {
            trainer->Tick();
        }
    }
}

void Environment::Train()
{
    if (!isEpisodeRunning)
    {
        return;
    }
    
    for (auto& [agent, inout] : agents)
    {
        auto& [inputGatherer, outputs] = inout;
        agent->GatherInput(inputGatherer);
    }

    for (auto& [agent, inout] : agents)
    {
        auto& [inputGatherer, outputs] = inout;
        agent->Think(inputGatherer, outputs);
    }

    for (auto& [agent, inout] : agents)
    {
        auto& [inputGatherer, outputs] = inout;
        agent->ApplyAction(outputs);
    }

    for (auto& [agent, inout] : agents)
    {
        float reward = 0.0f;
        agent->ComputeReward(reward);

        agent->ProcessReward(reward);
    }
}

void Environment::RegisterAgent(Agent* agent)
{
    agent->SetId(nextAgentId);
    
    agents.push_back(agent);

    std::cout << "Registered agent " << nextAgentId++ << std::endl;
}

void Environment::BeginEpisode()
{
    for (auto& [agent, inout] : agents)
    {
        auto& [inputGatherer, outputs] = inout;
        inputGatherer->Reset();
        outputs->Reset();
        agent->OnEpisodeBegin();
    }

    OnEpisodeBegin();
}

void Environment::EndEpisode()
{
    for (auto& [agent, inout] : agents)
    {
        agent->OnEpisodeEnd();
    }

    OnEpisodeEnd();
}
