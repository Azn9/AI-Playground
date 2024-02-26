#pragma once

class Environment;

class Trainer
{
public:
    Trainer(Environment *environment) : environment(environment) {}
    virtual ~Trainer() = default;

    virtual void Learn(int episodes) = 0;
    
protected:
    Environment *environment;
};
