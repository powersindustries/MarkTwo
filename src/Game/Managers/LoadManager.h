#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <map>

#include "Core/Types/String.h"


namespace MarkTwo
{


struct TextureAssetData
{
    TextureAssetData() : m_Texture(nullptr), m_iHeight(0), m_iWidth(0), m_uiFrames(0) {}

    CoreTypes::String m_ID;
    CoreTypes::String m_File;

    SDL_Texture* m_Texture;
    
    uint8_t m_uiFrames;
    
    int m_iWidth;
    int m_iHeight;
};


struct FontAssetData
{
    FontAssetData() : m_Font(nullptr) {}

    CoreTypes::String m_ID;
    CoreTypes::String m_File;

    TTF_Font* m_Font;
};


class LoadManager
{
public:
    LoadManager();
    ~LoadManager();

    void InitialLoad(SDL_Renderer* renderer);

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    std::map<uint32_t, TextureAssetData> m_TextureAssets; // ID as hash, Texture Data
    std::map<uint32_t, FontAssetData> m_FontAssets; // ID as hash, Texture Data


private:

    void LoadTextureAssets(SDL_Renderer* renderer);
    void LoadFontAssets(SDL_Renderer* renderer);


private:

    CoreTypes::String m_sManifestFilepath;
    CoreTypes::String m_sTextureDirectorypath;
    CoreTypes::String m_sFontsDirectorypath;

};

extern LoadManager g_LoadManager;
}