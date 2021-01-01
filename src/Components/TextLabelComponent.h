#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class TextLabelComponent : public MarkTwo::GameCore::Component
        {
        public:
            TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color)
            {
                m_Position.x = x;
                m_Position.y = y;
                m_Text = text;
                m_FontFamily = fontFamily;
                m_Color = color;
                SetLabelText(text, fontFamily);
            }

            void SetLabelText(std::string text, std::string fontFamily)
            {
                SDL_Surface* surface = TTF_RenderText_Blended(Game::m_AssetManager->GetFont(fontFamily), text.c_str(), m_Color);
                m_Texture = SDL_CreateTextureFromSurface(Game::m_Renderer, surface);
                SDL_FreeSurface(surface);
                SDL_QueryTexture(m_Texture, NULL, NULL, &m_Position.w, &m_Position.h);

            }

            void Render() override
            {
                FontManager::Draw(m_Texture, m_Position);
            }

        private:
            SDL_Rect m_Position;
            std::string m_Text;
            std::string m_FontFamily;
            SDL_Color m_Color;
            SDL_Texture* m_Texture;

        };

    }
}
