#include "AI/Public/Academy.h"

#include "AI/Public/Environment.h"

void Academy::Initialize()
{
    
}

void Academy::RegisterEnvironment(Environment* environment)
{
    environments.push_back(environment);
}

void Academy::PhysicsUpdate()
{
    for (auto environment : environments)
    {
        environment->Tick();
    }
}
