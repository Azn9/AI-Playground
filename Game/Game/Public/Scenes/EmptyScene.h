#pragma once

#include "Api/Public/Scene/Scene.h"
#include "Core/Public/Util/Singleton.h"

class EmptyScene final : public PM3D_API::Scene, public PM3D::CSingleton<EmptyScene>
{
public:
    EmptyScene() : Scene("EmptyScene")
    {
    }

    void Initialize() override;
    void InitializePhysics() override;
    void InitializeCamera() override;
    void InitializeLights() override;
    void InitializeObjects() override;
    void InitializeUI() override;
};
