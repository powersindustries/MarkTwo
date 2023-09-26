#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <SDL_mixer.h>
#include <map>
#include <string>
#include <vector>

namespace Core
{

struct TextureAssetData
{
    TextureAssetData() 
        : m_Texture(nullptr), m_uiID(0), m_iHeight(0), m_iWidth(0), m_uiFrames(0)
    {}

    uint32_t m_uiID;

    std::string m_File;

    SDL_Texture* m_Texture;

    uint8_t m_uiFrames;

    int m_iWidth;
    int m_iHeight;
};

class TileMapAssetData
{
public:
    TileMapAssetData() 
        : m_TextureAssetData(nullptr), m_uiID(0), m_uiLength(0)
    {}

    uint32_t m_uiID;

    TextureAssetData* m_TextureAssetData;

    uint8_t m_uiLength;

    std::vector<SDL_Rect> m_SourceRectangles;
};


struct FontAssetData
{
    FontAssetData() 
        : m_Font(nullptr), m_uiID(0)
    {}

    uint32_t m_uiID;
    std::string m_File;

    TTF_Font* m_Font;
};


struct SoundAssetData
{
    SoundAssetData() 
        : m_SoundEffect(nullptr), m_uiID(0)
    {}

    uint32_t m_uiID;
    std::string m_File;

    Mix_Chunk* m_SoundEffect;
};


struct MusicAssetData
{
    MusicAssetData() 
        : m_Music(nullptr), m_uiID(0)
    {}

    uint32_t m_uiID;
    std::string m_File;

    Mix_Music* m_Music;
};


class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    void Initialize(SDL_Renderer* renderer);

    SDL_Surface* GetAssetSurfaceByID(std::string AssetID);

    std::map<uint32_t, TextureAssetData> m_TextureAssets; // ID as hash, Texture Data
    std::map<uint32_t, TileMapAssetData> m_TileMapAssets; // ID as hash, TileMap Data
    std::map<uint32_t, FontAssetData> m_FontAssets; // ID as hash, Font Data
    std::map<uint32_t, SoundAssetData> m_SoundAssets; // ID as hash, Sound Data
    std::map<uint32_t, MusicAssetData> m_MusicAssets; // ID as hash, Music Data


private:

    void LoadTextureAssets(SDL_Renderer* renderer);
    void LoadTileMapAssets();
    void LoadFontAssets(SDL_Renderer* renderer);
    void LoadSoundAssets();
    void LoadMusicAssets();


private:

    std::string m_sManifestFilepath;
    std::string m_sTextureDirectorypath;
    std::string m_sFontsDirectorypath;
    std::string m_sSoundsDirectorypath;
    std::string m_sSaveDirectorypath;

};

extern AssetManager g_AssetManager;
}
