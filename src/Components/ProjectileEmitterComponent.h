#pragma once
#include "../../lib/glm/glm.hpp"
#include "../Utilities/Math.h"

#include "../EntityManager.h"
#include "TransformComponent.h"

using namespace MarkTwo::Utilities;
namespace MarkTwo
{
    namespace GameCore
    {
        class ProjectileEmitterComponent : public Component
        {
        public:
            ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop)
            {
                m_Speed = speed;
                m_Range = range;
                m_bShouldLoop = shouldLoop;
                m_AngleRad = MarkTwo::Utilities::g_Math.DegreesToRadians(static_cast<float>(angleDeg));
            }

            void Initialize() override
            {
                m_Transform = m_Owner->GetComponent<TransformComponent>();
                m_OriginPoint = glm::vec2(m_Transform->position.x, m_Transform->position.y);
                m_Transform->velocity = glm::vec2(glm::cos(m_AngleRad) * m_Speed, glm::sin(m_AngleRad) * m_Speed);
            }

            void Update(float deltaTime) override
            {
                if (glm::distance(m_Transform->position, m_OriginPoint) > m_Range)
                {
                    if (m_bShouldLoop)
                    {
                        m_Transform->position.x = m_OriginPoint.x;
                        m_Transform->position.y = m_OriginPoint.y;
                    }
                    else
                    {
                        m_Owner->Destroy();
                    }
                }
            }

        private:
            TransformComponent* m_Transform;
            glm::vec2 m_OriginPoint;
            
            int m_Speed;
            int m_Range;
            
            float m_AngleRad; // as radians
            bool m_bShouldLoop; // destroy after done, or repeat

        };

    }
}
