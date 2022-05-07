#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include <map>

namespace MarkTwo
{
struct TextureAssetData
{
    std::string m_ID;
    std::string m_File;

    SDL_Texture* m_Texture;

    int m_Fontsize;
    int m_TextureWidth;
    int m_TextureHeight;
};

struct FontAssetData
{
    std::string m_ID;
    std::string m_File;

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

    std::map<std::string, TextureAssetData> m_TextureAssets;
    std::map<std::string, FontAssetData> m_FontAssets;


private:

    std::string m_sManifestFilepath;
    std::string m_sTextureDirectorypath;
    std::string m_sFontsDirectorypath;

};

extern LoadManager g_LoadManager;
}