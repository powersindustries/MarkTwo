#ifndef AssetManager_h
#define AssetManager_h

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
        : m_Texture(nullptr), m_uiId(0), m_iHeight(0), m_iWidth(0), m_uiFrames(0)
    {}

    uint32_t m_uiId;

    std::string m_sFile;

    SDL_Texture* m_Texture;

    uint8_t m_uiFrames;

    int m_iWidth;
    int m_iHeight;
};

class TileMapAssetData
{
public:
    TileMapAssetData() 
        : m_TextureAssetData(nullptr), m_uiId(0), m_uiLength(0)
    {}

    uint32_t m_uiId;

    TextureAssetData* m_TextureAssetData;

    uint8_t m_uiLength;

    std::vector<SDL_Rect> m_SourceRectangles;
};


struct FontAssetData
{
    FontAssetData() 
        : m_Font(nullptr), m_uiId(0)
    {}

    uint32_t m_uiId;
    std::string m_sFile;

    TTF_Font* m_Font;
};


struct SoundAssetData
{
    SoundAssetData() 
        : m_SoundEffect(nullptr), m_uiId(0)
    {}

    uint32_t m_uiId;
    std::string m_sFile;

    Mix_Chunk* m_SoundEffect;
};


struct MusicAssetData
{
    MusicAssetData() 
        : m_Music(nullptr), m_uiId(0)
    {}

    uint32_t m_uiId;
    std::string m_sFile;

    Mix_Music* m_Music;
};


class AssetManager
{
public:
    AssetManager();

    void Initialize(SDL_Renderer* renderer);

    SDL_Surface* GetAssetSurfaceById(const std::string& assetId);

    std::map<uint8_t, TextureAssetData> m_TextureAssetsMap; // ID as hash, Texture Data
    std::map<uint8_t, TileMapAssetData> m_TileMapAssetsMap; // ID as hash, TileMap Data
    std::map<uint8_t, FontAssetData> m_FontAssetsMap; // ID as hash, Font Data
    std::map<uint8_t, SoundAssetData> m_SoundAssetsMap; // ID as hash, Sound Data
    std::map<uint8_t, MusicAssetData> m_MusicAssetsMap; // ID as hash, Music Data


private:

    void LoadTextureAssets(SDL_Renderer* renderer);
    void LoadTileMapAssets();
    void LoadFontAssets(SDL_Renderer* renderer);
    void LoadSoundAssets();
    void LoadMusicAssets();


private:

    std::string m_sManifestFilepath;
    std::string m_sTextureDirectoryPath;
    std::string m_sFontsDirectoryPath;
    std::string m_sSoundsDirectoryPath;
    std::string m_sSaveDirectoryPath;

};

extern AssetManager g_AssetManager;
}

#endif