#include "AssetManager.h"


namespace MarkTwo
{
    namespace GameCore
    {
       
        
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        AssetManager::AssetManager(EntityManager* manager)
        {
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        AssetManager::~AssetManager()
        {
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void AssetManager::ClearData()
        {
            m_Textures.clear();
            m_Fonts.clear();
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void AssetManager::AddTexture(std::string textureId, const char* filePath)
        {
            m_Textures.emplace(textureId, TextureManager::LoadTexture(filePath));
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize)
        {
            m_Fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void AssetManager::AddSound(std::string soundId, std::string filePath)
        {
            // <AssetID, Filepath>
            m_Sounds.emplace(soundId, filePath);
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        std::string AssetManager::GetSound(std::string soundId)
        {
            return m_Sounds[soundId];
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        SDL_Texture* AssetManager::GetTexture(std::string textureId)
        {
            return m_Textures[textureId];
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        TTF_Font* AssetManager::GetFont(std::string fontId)
        {
            return m_Fonts[fontId];
        }

    }
}
