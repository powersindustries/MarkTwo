#include "MapManager.h"
#include <cctype>
#include <cmath>
#include <vector>

#include "rapidxml_utils.hpp"

#include "GameGlobals.h"
#include "Core/Systems/Logging.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Managers/AssetManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
MapManager g_MapManager;


// -------------------------------------------------------
// -------------------------------------------------------
MapManager::MapManager()
    : m_ActiveMapData(nullptr)
{
    m_sMapManifestPath.append(__PROJECT_DIRECTORY__);
    m_sMapManifestPath.append("/src/Data/MapsManifest.xml");

    m_sMapDirectoryPath.append(__PROJECT_DIRECTORY__);
    m_sMapDirectoryPath.append("/src/Data/Maps/");

    m_sTileMapDirectoryPath.append(__PROJECT_DIRECTORY__);
    m_sTileMapDirectoryPath.append("/src/Data/TileMaps/");
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::Initialize()
{
    LoadTileMapData();
    LoadMapData();

    LoadMapByID(Core::StringToHash32(std::string("mp_1")));

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Map data Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::Draw(SDL_Renderer* renderer)
{
    const uint32_t tileMapIndex = m_ActiveMapData->m_uiTileMap;
    const TileMapData& currTileMapData = m_TileMapData[tileMapIndex];
    Core::TileMapAssetData tileMapAssetData = Core::g_AssetManager.m_TileMapAssetsMap[currTileMapData.m_uiTileMapID];

    const uint8_t mapSize = static_cast<uint8_t>(currTileMapData.m_vMap.size());
    for (uint8_t x = 0; x < mapSize; ++x)
    {
        const uint8_t testInt = currTileMapData.m_vMap[x];

        SDL_RenderCopy(
            renderer,
            tileMapAssetData.m_TextureAssetData->m_Texture,
            &tileMapAssetData.m_SourceRectangles[currTileMapData.m_vMap[x]],
            &currTileMapData.m_vScreenTiles[x]
        );
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapByID(const uint32_t uiMapID)
{
    if (m_MapData.count(uiMapID))
    {
        m_ActiveMapData = &m_MapData[uiMapID];
    }
    else
    {
        std::string errorMessage = "The key: ";
        errorMessage.append(std::to_string(uiMapID));
        errorMessage.append(", does not exist in the m_MapData.");

        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadTileMapData()
{
    rapidxml::file<> xmlFile(m_sMapManifestPath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* mapNode = doc.first_node()->first_node("TileMaps");
    if (mapNode)
    {
        for (rapidxml::xml_node<>* child = mapNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in LoadTileMapData method is nullptr.");
                continue;
            }

            std::string tileMapPath = m_sTileMapDirectoryPath;
            tileMapPath.append(child->first_attribute("File")->value());

            LoadTileMapDataByPath(tileMapPath);
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapData()
{
    rapidxml::file<> xmlFile(m_sMapManifestPath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* mapNode = doc.first_node()->first_node("Maps");
    if (mapNode)
    {
        for (rapidxml::xml_node<>* child = mapNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in LoadMapData method is nullptr.");
                continue;
            }

            std::string mapPath = m_sMapDirectoryPath;
            mapPath.append(child->first_attribute("File")->value());

            LoadMapDataByPath(mapPath);
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadTileMapDataByPath(const std::string& mapPath)
{
    rapidxml::file<> xmlFile(mapPath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* mapNode = doc.first_node("Map");
    if (mapNode)
    {
        TileMapData newTileMap;
        newTileMap.m_uiID = Core::StringToHash32(mapNode->first_attribute("ID")->value());
        newTileMap.m_uiTileMapID = Core::StringToHash32(mapNode->first_attribute("Texture")->value());

        std::string mapValues = mapNode->first_attribute("Values")->value();

        // Create vector of comma seperated values.
        const uint8_t mapValuesSize = static_cast<uint32_t>(mapValues.size());
        for (uint8_t x = 0; x < mapValuesSize; ++x)
        {
            char currChar = mapValues[x];
            if (std::isdigit(currChar))
            {
                newTileMap.m_vMap.push_back(((uint8_t)(currChar)) - 48);
            }
        }

        uint8_t row = 0;
        const uint8_t mapSize = static_cast<uint8_t>(newTileMap.m_vMap.size());
        const uint8_t length = static_cast<uint8_t>(std::sqrt(mapSize));
        for (uint8_t x = 0; x < mapSize; ++x)
        {
            // Calculate current row.
            if (x != 0 && x % length == 0)
            {
                row++;
            }

            SDL_Rect newRect;
            newRect.x = (x - (row * length)) * g_GameGlobals.TILE_SIZE;
            newRect.y = row * g_GameGlobals.TILE_SIZE;

            newRect.w = g_GameGlobals.TILE_SIZE;
            newRect.h = g_GameGlobals.TILE_SIZE;

            newTileMap.m_vScreenTiles.push_back(newRect);
        }

        m_TileMapData.insert({ newTileMap.m_uiID, newTileMap });
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapDataByPath(const std::string& mapPath)
{
    rapidxml::file<> xmlFile(mapPath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* mapNode = doc.first_node("Map");
    if (mapNode)
    {
        MapData newMap;
        newMap.m_uiID = Core::StringToHash32(std::string(mapNode->first_attribute("ID")->value()));
        newMap.m_uiTileMap = Core::StringToHash32(std::string(mapNode->first_attribute("TileMap")->value()));

        // Populate background colors.
        const std::string background = mapNode->first_attribute("Background")->value();
        const uint8_t backgroundSize = static_cast<uint8_t>(background.size());

        std::vector<int> backgroundVector;
        std::string tempString = "";
        for (uint8_t x = 0; x < backgroundSize; ++x)
        {
            char currChar = background[x];
            if (currChar != ',' && currChar != ' ')
            {
                tempString += currChar;
            }
            else
            {
                backgroundVector.push_back(std::stoi(tempString));
                tempString = "";
            }
        }
        backgroundVector.push_back(std::stoi(tempString));

        newMap.m_BackgroundColor.r = backgroundVector[0];
        newMap.m_BackgroundColor.g = backgroundVector[1];
        newMap.m_BackgroundColor.b = backgroundVector[2];
        newMap.m_BackgroundColor.a = backgroundVector[3];

        newMap.m_BackgroundRectangle.x = 0;
        newMap.m_BackgroundRectangle.y = 0;
        newMap.m_BackgroundRectangle.w = Core::g_SettingsManager.GetScreenWidth();
        newMap.m_BackgroundRectangle.h = Core::g_SettingsManager.GetScreenHeight();

        m_MapData.insert({ newMap.m_uiID, newMap });
    }

}

}
