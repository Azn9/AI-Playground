#pragma once

class Environment;

class Trainer
{
public:
    Trainer(Environment *environment) : environment(environment) {}
    virtual ~Trainer() = default;

    virtual void Learn(int episodes) = 0;
    virtual void AddReward(float reward) = 0;
    virtual void AddActions(const at::Tensor& tensor, double log_prob) = 0;

protected:
    Environment *environment;
};
