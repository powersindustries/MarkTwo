#pragma once
#include <SDL.h>

#include "TransformComponent.h"

#include "../Component.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class SpriteComponent : public MarkTwo::GameCore::Component
        {
        public:
            SDL_RendererFlip m_SpriteFlip = SDL_FLIP_NONE;

            SpriteComponent(const char* filePath)
            {
                m_bIsAnimated = false;
                m_bIsFixed = false;

                SetTexture(filePath);
            }
            
            SpriteComponent(std::string assetTextureID)
            {
                m_bIsAnimated = false;
                m_bIsFixed = false;

                SetTexture(assetTextureID);
            }
            
            SpriteComponent(std::string assetTextureID, bool isFixed)
            {
                m_bIsAnimated = false;
                m_bIsFixed = isFixed;

                SetTexture(assetTextureID);
            }

            SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed)
            {
                m_bIsAnimated = true;
                m_bIsFixed = isFixed;

                m_iFrameNumber = numFrames;
                m_iAnimationSpeed = animationSpeed;

                if (hasDirections)
                {
                    Animation downAnimation = Animation(0, numFrames, animationSpeed);
                    Animation rightAnimation = Animation(1, numFrames, animationSpeed);
                    Animation leftAnimation = Animation(2, numFrames, animationSpeed);
                    Animation upAnimation = Animation(3, numFrames, animationSpeed);

                    m_Animations.emplace("downAnimation", downAnimation);
                    m_Animations.emplace("rightAnimation", rightAnimation);
                    m_Animations.emplace("leftAnimation", leftAnimation);
                    m_Animations.emplace("upAnimation", upAnimation);

                    m_uiAnimationIndex = 0;
                    m_CurrentAnimationName = "downAnimation";

                }
                else
                {
                    Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                    m_Animations.emplace("SingleAnimation", singleAnimation);
                    m_uiAnimationIndex = 0;
                    m_CurrentAnimationName = "SingleAnimation"; // maybe add name field to animations?
                }

                Play(m_CurrentAnimationName);
                SetTexture(id);
            }

            void Play(std::string animationName)
            {
                m_iFrameNumber = m_Animations[animationName].m_uiFrameNumbers;
                m_uiAnimationIndex = m_Animations[animationName].m_uiIndex;
                m_iAnimationSpeed = m_Animations[animationName].m_uiAnimationSpeed;
                m_CurrentAnimationName = animationName;
            }

            void SetTexture(std::string assetTextureId)
            {
                texture = Game::m_AssetManager->GetTexture(assetTextureId);
            }

            void Initialize() override
            {
                m_Transform = m_Owner->GetComponent<TransformComponent>();
                m_SourceRectangle.x = 0;
                m_SourceRectangle.y = 0;
                m_SourceRectangle.w = m_Transform->width;
                m_SourceRectangle.h = m_Transform->height;
            }

            void Update(float deltaTime) override
            {
                if (m_bIsAnimated)
                {
                    // calculate movement of animation frames
                    m_SourceRectangle.x = m_SourceRectangle.w * static_cast<int>(SDL_GetTicks() / m_iAnimationSpeed % m_iFrameNumber);
                }

                m_SourceRectangle.y = m_uiAnimationIndex * m_Transform->height;

                m_DestinationRectangle.x = static_cast<int>(m_Transform->position.x) - (m_bIsFixed ? 0 : Game::m_Camera.x); // make sure ui/fixed elements stay in place
                m_DestinationRectangle.y = static_cast<int>(m_Transform->position.y) - (m_bIsFixed ? 0 : Game::m_Camera.y); // make sure ui/fixed elements stay in place
                m_DestinationRectangle.w = m_Transform->width * m_Transform->scale;
                m_DestinationRectangle.h = m_Transform->height * m_Transform->scale;
            }

            void Render() override
            {
                TextureManager::Draw(texture, m_SourceRectangle, m_DestinationRectangle, m_SpriteFlip);
            }

        private:
            TransformComponent* m_Transform;

            SDL_Texture* texture;
            SDL_Rect m_SourceRectangle;
            SDL_Rect m_DestinationRectangle;

            std::map<std::string, Animation> m_Animations;
            std::string m_CurrentAnimationName;

            bool m_bIsFixed; // stays in same position, doenst move
            bool m_bIsAnimated;

            int m_iFrameNumber;
            int m_iAnimationSpeed;

            unsigned int m_uiAnimationIndex = 0;

        };

    }
}
