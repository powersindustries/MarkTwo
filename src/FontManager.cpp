#include "FontManager.h"

namespace MarkTwo
{
    namespace GameCore
    {


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        TTF_Font* FontManager::LoadFont(const char* fileName, int fontSize)
        {
            return TTF_OpenFont(fileName, fontSize);
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void FontManager::Draw(SDL_Texture* texture, SDL_Rect position)
        {
            SDL_RenderCopy(Game::m_Renderer, texture, NULL, &position);
        }

    }
}
