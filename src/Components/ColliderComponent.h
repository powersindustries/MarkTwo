#pragma once
#include <string>

#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class ColliderComponent : public Component
        {
        public:
            ColliderComponent(std::string colliderTag, int x, int y, int width, int height)
            {
                m_ColliderTag = colliderTag;
                m_Collider = { x, y, width, height };
            }

            void Initialize() override
            {
                if (m_Owner->HasComponent<TransformComponent>())
                {
                    m_Transform = m_Owner->GetComponent<TransformComponent>();
                    m_SourceRectangle = { 0, 0, m_Transform->width, m_Transform->height };
                    m_DestinationRectangle = { m_Collider.x, m_Collider.y, m_Collider.w, m_Collider.h };
                }
            }

            void Update(float deltaTime) override
            {
                m_Collider.x = static_cast<int>(m_Transform->position.x);
                m_Collider.y = static_cast<int>(m_Transform->position.y);
                m_Collider.w = m_Transform->width * m_Transform->scale;
                m_Collider.h = m_Transform->height * m_Transform->scale;

                m_DestinationRectangle.x = m_Collider.x - MarkTwo::GameCore::Game::m_Camera.x;
                m_DestinationRectangle.y = m_Collider.y - MarkTwo::GameCore::Game::m_Camera.y;
            }


        public:
            std::string m_ColliderTag;
            SDL_Rect m_Collider;
            SDL_Rect m_SourceRectangle;
            SDL_Rect m_DestinationRectangle;
            TransformComponent* m_Transform;

        };
    }
}

