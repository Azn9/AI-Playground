#pragma once
#include <vector>

#include "Api/Public/Component/Component.h"

class Environment;

class Academy : public PM3D_API::Component
{
public:
    void Initialize() override;

    void RegisterEnvironment(Environment* environment);

    void PhysicsUpdate() override;

private:
    std::vector<Environment*> environments;
};
