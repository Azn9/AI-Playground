#pragma once
#include "Api/Public/Scene/Scene.h"
#include "Core/Public/Util/Singleton.h"

class GoToGoalScene : public PM3D_API::Scene, public PM3D::CSingleton<GoToGoalScene>
{
public:
    void InitializePhysics() override;
    void InitializeCamera() override;
    void InitializeLights() override;
    void InitializeObjects() override;
    void InitializeUI() override;
    void PostInitialize() override;
    void DrawSelf() const override;
};
