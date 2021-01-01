#pragma once
#include <map>
#include <string>
#include <SDL_ttf.h>
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class AssetManager
        {
        public:
            AssetManager(EntityManager* manager);
            ~AssetManager();

            void ClearData();

            void AddTexture(std::string textureId, const char* filePath);
            SDL_Texture* GetTexture(std::string textureId);

            void AddFont(std::string fontId, const char* filePath, int fontSize);
            TTF_Font* GetFont(std::string fontId);

            void AddSound(std::string soundId, std::string filePath);
            std::string GetSound(std::string soundId);

        private:
            EntityManager* m_Manager;

            std::map<std::string, SDL_Texture*> m_Textures;
            std::map<std::string, TTF_Font*>    m_Fonts;
            
            std::map<std::string, std::string>  m_Sounds;
        };
    }
}
