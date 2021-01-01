#pragma once
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerProjectileEmitterController.h"
#include "../Components/ColliderComponent.h"
#include "../SoundManager.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class KeyboardControlComponent : public MarkTwo::GameCore::Component
        {
        public:
            KeyboardControlComponent() 
            {
            }

            KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey)
            {
                m_UpKey    = GetSDLKeyStringCode(upKey);
                m_RightKey = GetSDLKeyStringCode(rightKey);
                m_DownKey  = GetSDLKeyStringCode(downKey);
                m_LeftKey  = GetSDLKeyStringCode(leftKey);

                m_ShootKey = GetSDLKeyStringCode(shootKey);
            
            }

            void Initialize() override
            {
                m_Transform = m_Owner->GetComponent<TransformComponent>();
                m_Sprite = m_Owner->GetComponent<SpriteComponent>();
            }

            void Update(float deltaTime) override
            {
                if (Game::m_Event.type == SDL_KEYDOWN)
                {
                    std::string keycode = std::to_string(Game::m_Event.key.keysym.sym);
                    if (keycode.compare(m_UpKey) == 0)
                    {
                        m_Transform->velocity.y = -50;
                        m_Transform->velocity.x = 0;
                        m_Sprite->Play("upAnimation");
                    }
                    if (keycode.compare(m_RightKey) == 0)
                    {
                        m_Transform->velocity.y = 0;
                        m_Transform->velocity.x = 50;
                        m_Sprite->Play("rightAnimation");
                    }
                    if (keycode.compare(m_DownKey) == 0)
                    {
                        m_Transform->velocity.y = 50;
                        m_Transform->velocity.x = 0;
                        m_Sprite->Play("downAnimation");
                    }
                    if (keycode.compare(m_LeftKey) == 0)
                    {
                        m_Transform->velocity.y = 0;
                        m_Transform->velocity.x = -50;
                        m_Sprite->Play("leftAnimation");
                    }

                    if (keycode.compare(m_ShootKey) == 0)
                    {
                        // Shooting Logic to be added here
                    }
                }

                if (Game::m_Event.type == SDL_KEYUP)
                {
                    std::string keycode = std::to_string(Game::m_Event.key.keysym.sym);
                    if (keycode.compare(m_UpKey) == 0)
                    {
                        m_Transform->velocity.y = 0;
                    }
                    if (keycode.compare(m_RightKey) == 0)
                    {
                        m_Transform->velocity.x = 0;
                    }
                    if (keycode.compare(m_DownKey) == 0)
                    {
                        m_Transform->velocity.y = 0;
                    }
                    if (keycode.compare(m_LeftKey) == 0)
                    {
                        m_Transform->velocity.x = 0;
                    }
                }
            }
            
            std::string GetSDLKeyStringCode(std::string keyCode)
            {
                // Up
                if (keyCode.compare("up") == 0)
                {
                    return "1073741906";
                }

                // Down
                if (keyCode.compare("down") == 0)
                {
                    return "1073741905";
                }

                // Left
                if (keyCode.compare("left") == 0)
                {
                    return "1073741904";
                }

                // Right
                if (keyCode.compare("right") == 0)
                {
                    return "1073741903";
                }

                // Space
                if (keyCode.compare("space") == 0)
                {
                    return "32";
                }

                return std::to_string(static_cast<int>(keyCode[0]));
            }



        public:
            std::string m_UpKey;
            std::string m_DownKey;
            std::string m_RightKey;
            std::string m_LeftKey;

            std::string m_ShootKey;

            TransformComponent* m_Transform;
            SpriteComponent* m_Sprite;

        };

    }
}
