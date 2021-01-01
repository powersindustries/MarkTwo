#pragma once
#include <SDL.h>
#include "../../lib/glm/glm.hpp"

#include "../Game.h"
#include "../Component.h"
#include "../EntityManager.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class TileComponent : public MarkTwo::GameCore::Component
        {
        public:
            TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId)
            {
                m_Texture = Game::m_AssetManager->GetTexture(assetTextureId);

                m_SourceRectangle.x = sourceRectX;
                m_SourceRectangle.y = sourceRectY;
                m_SourceRectangle.w = tileSize;
                m_SourceRectangle.h = tileSize;

                m_DestinationRectangle.x = x;
                m_DestinationRectangle.y = y;
                m_DestinationRectangle.w = tileSize * tileScale;
                m_DestinationRectangle.h = tileSize * tileScale;

                m_Position.x = x;
                m_Position.y = y;
            }

            ~TileComponent()
            {
                SDL_DestroyTexture(m_Texture);
            }

            void Update(float deltaTime) override
            {
                m_DestinationRectangle.x = m_Position.x - Game::m_Camera.x;
                m_DestinationRectangle.y = m_Position.y - Game::m_Camera.y;
            }

            void Render() override
            {
                TextureManager::Draw(m_Texture, m_SourceRectangle, m_DestinationRectangle, SDL_FLIP_NONE);
            }

        public:
            SDL_Texture* m_Texture;
            SDL_Rect m_SourceRectangle;
            SDL_Rect m_DestinationRectangle;

            glm::vec2 m_Position;
        };

    }
}
