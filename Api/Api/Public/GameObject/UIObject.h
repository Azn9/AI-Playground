#pragma once

#include <DirectXMath.h>
#include <memory>
#include <string>
#include <vector>

#include "Api/Public/Component/UIComponent.h"
#include "Api/Public/Util/Instanceof.h"

namespace PM3D_API
{
    class UICanvas;

    class UIObject
    {
    public:
        UIObject(
            const std::string& name,
            const DirectX::XMFLOAT2& scale,
            const DirectX::XMFLOAT2& position = {0.f, 0.f},
            const float rotation = 0.f,
            bool relativeScale = false,
            bool relativePosition = false
        );
        virtual ~UIObject();

        virtual void Initialize();
        virtual void Update();
        virtual void Draw();

        virtual void AddComponent(std::unique_ptr<UIComponent>&& component);

        std::string GetName() const { return name; }

        template <typename T, template_extends<T, UIComponent>  = 0>
        std::vector<T*> GetComponents()
        {
            std::vector<T*> components{};
            for (const auto component : components)
            {
                if (!component) continue;

                if (typeid(*component.get()) == typeid(T))
                {
                    components.push_back(static_cast<T*>(component.get()));
                }
            }

            return components;
        }

        const std::vector<std::unique_ptr<UIComponent>>& GetComponents() const { return components; }

        DirectX::XMFLOAT2 GetPosition() const { return position; }
        virtual void SetPosition(const DirectX::XMFLOAT2& newPosition) { position = newPosition; }

        DirectX::XMFLOAT2 GetScale() const { return scale; }
        virtual void SetScale(const DirectX::XMFLOAT2& newScale) { scale = newScale; }

        float GetRotation() const { return rotation; }
        virtual void SetRotation(const float newRotation) { rotation = newRotation; }

        void SetCentralRotation(const float newRotation);

        float GetAlpha() const { return alpha; }
        virtual void SetAlpha(const float newAlpha) { alpha = newAlpha; }

        virtual void OnHoverEnter()
        {
        }

        virtual void OnHoverExit()
        {
        }

        virtual void OnClickPressed()
        {
        }

        virtual void OnClickReleased()
        {
        }

        bool IsHovered() const { return isHovered; }
        void SetHovered(const bool newIsHovered) { isHovered = newIsHovered; }
        bool IsClicked() const { return isClicked; }
        void SetClicked(const bool newIsClicked) { isClicked = newIsClicked; }

    protected:
        std::string name = "Unnamed UI Object";

        float rotation;
        float alpha;

        DirectX::XMFLOAT2 position;
        DirectX::XMFLOAT2 scale;
        DirectX::XMFLOAT2 basePosition;
        DirectX::XMFLOAT2 basePositionComputed;
        DirectX::XMFLOAT2 baseScale;
        DirectX::XMFLOAT2 baseScaleComputed;
        bool relativeScale;
        bool relativePosition;

        std::vector<std::unique_ptr<UIComponent>> components{};

        bool isHovered = false;
        bool isClicked = false;

        friend UICanvas;
        UICanvas* canvas = nullptr;
        void UpdateScaleAndPosition();

        virtual void DrawSelf() const;

        void LogBeginDrawSelf() const;
        void LogEndDrawSelf() const;

    private:
        friend class Scene;
        void SetCanvas(UICanvas* newCanvas) { canvas = newCanvas; }

        mutable int64_t beginDrawSelf;
        mutable int64_t endDrawSelf;
    };
}
