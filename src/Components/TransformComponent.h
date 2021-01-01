#pragma once
#include <SDL.h>

#include "../../lib/glm/glm.hpp"

#include "../Game.h"
#include "../EntityManager.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class TransformComponent : public MarkTwo::GameCore::Component
        {
        public:
            glm::vec2 position;
            glm::vec2 velocity;
            int width;
            int height;
            int scale;

            TransformComponent(int posx, int posy, int velx, int vely, int w, int h, int s)
            {
                position = glm::vec2(posx, posy);
                velocity = glm::vec2(velx, vely);

                width = w;
                height = h;
                scale = s;
            }

            void Initialize() override
            {

            }

            void Update(float deltaTime) override
            {
                position.x += velocity.x * deltaTime;
                position.y += velocity.y * deltaTime;
            }

            void Render() override
            {
            }


        };

    }
}
