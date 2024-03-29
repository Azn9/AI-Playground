﻿#include "Api/Public/Scene/Scene.h"

#include <iostream>

#include "Api/Private/Light/Shadow/ShadowProcessor.h"

PM3D_API::Scene::~Scene()
{
    isDeleted = true;

    children.clear();
}

void PM3D_API::Scene::Initialize()
{
    scene = this;

    GameObject::Initialize();

    InitializePhysics();
    InitializeCamera();
    InitializeLights();
    InitializeObjects();
    InitializeUI();

    PostInitialize();
}

void PM3D_API::Scene::SetMainCamera(std::unique_ptr<Camera>&& newMainCamera)
{
    newMainCamera->SetScene(this);
    if (mainCamera != nullptr)
        mainCamera->SetScene(nullptr);
    mainCamera = newMainCamera.get();
    GameObject::AddChild(std::move(newMainCamera));
}

void PM3D_API::Scene::SetMainCamera(Camera* newMainCamera)
{
    // Check if newMainCamera is a child of this scene

    if (const auto it = std::find_if(children.begin(), children.end(),
                                             [newMainCamera](const std::unique_ptr<GameObject>& child)
                                             {
                                                 return child.get() == newMainCamera;
                                             }
    ); it == children.end())
    {
        throw std::runtime_error("newMainCamera is not a child of this scene");
    }

    mainCamera = newMainCamera;
}

void PM3D_API::Scene::SetPhysicsResolver(std::unique_ptr<PhysicsResolver>&& newPhysicsResolver)
{
    physicsEnabled = true;
    physicsResolver = newPhysicsResolver.get();

    GameObject::AddComponent(std::move(newPhysicsResolver));
}

void PM3D_API::Scene::Update()
{
    if (isDeleted) return;
    GameObject::Update();
}

void PM3D_API::Scene::PhysicsUpdate()
{
    if (isDeleted) return;

    GameObject::PhysicsUpdate();

    if (physicsEnabled && physicsResolver)
        physicsResolver->ResolvePhysics();
}

void PM3D_API::Scene::Draw()
{
    if (isDeleted) return;
    if (const auto shadowProcessor = GetComponent<ShadowProcessor>())
    {
        shadowProcessor->ProcessShadow();
    }

    GameObject::Draw();

    if (lightsNeedUpdate)
        lightsNeedUpdate = false;
}

void PM3D_API::Scene::DrawShadow(const Camera& camera)
{
    if (isDeleted) return;

    GameObject::DrawShadow(camera);
}

void PM3D_API::Scene::DrawSelf() const
{
    LogBeginDrawSelf();

    if (isDeleted) return;
    GameObject::DrawSelf();

    LogEndDrawSelf();
}

void PM3D_API::Scene::InitializeUI()
{
    /*uiCanvas = std::make_unique<UICanvas>();
    uiCanvas->scene = this;
    uiCanvas->Initialize();*/
}

void PM3D_API::Scene::AddUiChild(std::unique_ptr<UIObject>&& child) const
{
    if (!uiCanvas)
        throw std::runtime_error("Scene::AddUiChild: uiCanvas is not initialized");

    uiCanvas->AddChild(std::move(child));
}
