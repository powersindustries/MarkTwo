#ifndef MapManager_h
#define MapManager_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include <vector>
#include <map>

namespace MarkTwo
{

struct TileMapData
{
    uint8_t m_uiId;
    uint8_t m_uiTileMapId;

    std::vector<SDL_Rect> m_vScreenTiles;
    std::vector<uint8_t> m_vMap;
};

struct MapData
{
    uint8_t m_uiId;

    uint8_t m_uiTileMap;

    SDL_Color m_BackgroundColor;
    SDL_Rect m_BackgroundRectangle;
};

class MapManager
{
public:

    MapManager();

    void Initialize();
    void Draw(SDL_Renderer* renderer);

    void LoadMapById(const uint8_t uiMapId);


private:

    void LoadTileMapData();
    void LoadMapData();

    void LoadTileMapDataByPath(const std::string& mapPath);
    void LoadMapDataByPath(const std::string& mapPath);


private:

    MapData* m_ActiveMapData;

    std::map<uint32_t, MapData> m_MapData;
    std::map<uint32_t, TileMapData> m_TileMapData;

    std::string m_sMapManifestPath;
    std::string m_sMapDirectoryPath;
    std::string m_sTileMapDirectoryPath;

};

extern MapManager g_MapManager;
}

#endif