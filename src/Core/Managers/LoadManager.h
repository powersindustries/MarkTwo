#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <map>

#include "../Types/String.h"

namespace MarkTwo
{


struct TextureAssetData
{
    TextureAssetData() : m_Fontsize(0), m_Texture(nullptr), m_TextureHeight(0), m_TextureWidth(0) {}

    CoreTypes::String m_ID;
    CoreTypes::String m_File;

    SDL_Texture* m_Texture;

    int m_Fontsize;
    int m_TextureWidth;
    int m_TextureHeight;
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

    void Update(float* deltaTime);
    void Draw(SDL_Renderer* renderer);

    std::map<CoreTypes::String, TextureAssetData> m_TextureAssets;
    std::map<CoreTypes::String, FontAssetData> m_FontAssets;


private:

    CoreTypes::String m_sManifestFilepath;
    CoreTypes::String m_sTextureDirectorypath;
    CoreTypes::String m_sFontsDirectorypath;

};

extern LoadManager g_LoadManager;
}