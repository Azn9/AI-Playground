#pragma once

class Agent;

class Trainer
{
public:
    Trainer(Agent *agent) : agent(agent) {}
    virtual ~Trainer() = default;

    virtual void Learn(int episodes) = 0;
    virtual void Tick() = 0;
    virtual void AddReward(float reward) = 0;
    virtual void AddActions(const at::Tensor& tensor, double log_prob) = 0;

protected:
    Agent* agent = nullptr;
};
