#include "MapManager.h"
#include "GameGlobals.h"

#include "Core/Systems/Logging.h"
#include "Core/Systems/Hash.h"
#include "Core/Types/LuaTableLoader.h"
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
	m_sMapManifestPath.append("/src/Data/MapsManifest.lua");

	m_sMapDirectoryPath.append(__PROJECT_DIRECTORY__);
	m_sMapDirectoryPath.append("/src/Data/Maps/");

	m_sTileMapDirectoryPath.append(__PROJECT_DIRECTORY__);
	m_sTileMapDirectoryPath.append("/src/Data/TileMaps/");
}


// -------------------------------------------------------
// -------------------------------------------------------
MapManager::~MapManager()
{
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
	const uint32_t uiTilemapIndex = m_ActiveMapData->m_uiTileMap;
	const TileMapData* currTileMapData = &m_TileMapData[uiTilemapIndex];
	Core::TileMapAssetData tileMapAssetData = Core::g_AssetManager.m_TileMapAssets[currTileMapData->m_uiTileMapID];

	const uint8_t uiMapSize = static_cast<uint8_t>(currTileMapData->m_vMap.size());
	for (uint8_t x=0; x < uiMapSize; ++x)
	{
		SDL_RenderCopy(
			renderer, 
			tileMapAssetData.m_TextureAssetData->m_Texture, 
			&tileMapAssetData.m_SourceRectangles[currTileMapData->m_vMap[x]],
			&currTileMapData->m_vScreenTiles[x]
		);
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapByID(uint32_t uiMapID)
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
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sMapManifestPath);

	luaLoader->LoadTableByID("TileMaps");

	const uint8_t uiMapsTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiMapsTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

		std::string sTileMapPath = m_sTileMapDirectoryPath;
		sTileMapPath.append(luaLoader->GetStringByID("File"));
		LoadTileMapDataByPath(sTileMapPath);

		luaLoader->PopTopTableElement();
	}

	delete luaLoader;
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapData()
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sMapManifestPath);

	luaLoader->LoadTableByID("Maps");

	const uint8_t uiMapsTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiMapsTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

		std::string sMapPath = m_sMapDirectoryPath;
		sMapPath.append(luaLoader->GetStringByID("File"));
		LoadMapDataByPath(sMapPath);

		luaLoader->PopTopTableElement();
	}

	delete luaLoader;
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadTileMapDataByPath(std::string mapPath)
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(mapPath);

	luaLoader->LoadTableByID("Data");

	TileMapData newTileMap;
	newTileMap.m_uiID = Core::StringToHash32(luaLoader->GetStringByID("ID"));
	newTileMap.m_uiTileMapID = Core::StringToHash32(luaLoader->GetStringByID("Texture"));

	luaLoader->LoadTableByID("Map");
	const uint8_t uiTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

		newTileMap.m_vMap.push_back(luaLoader->GetTopValueAsInt());

		luaLoader->PopTopTableElement();
	}

	uint8_t uiRow = 0;

	const uint8_t uiMapSize = static_cast<uint8_t>(newTileMap.m_vMap.size());
	const uint8_t uiLength = static_cast<uint8_t>(std::sqrt(uiMapSize));
	for (uint8_t x = 0; x < uiMapSize; ++x)
	{
		// Calculate current row.
		if (x != 0 && x % uiLength == 0)
		{
			uiRow++;
		}

		SDL_Rect newRect;
		newRect.x = (x - (uiRow * uiLength)) * g_GameGlobals.TILE_SIZE;
		newRect.y = uiRow * g_GameGlobals.TILE_SIZE;

		newRect.w = g_GameGlobals.TILE_SIZE;
		newRect.h = g_GameGlobals.TILE_SIZE;

		newTileMap.m_vScreenTiles.push_back(newRect);
	}

	m_TileMapData.insert({ newTileMap.m_uiID, newTileMap });
}


// -------------------------------------------------------
// -------------------------------------------------------
void MapManager::LoadMapDataByPath(std::string mapPath)
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(mapPath);

	luaLoader->LoadTableByID("Settings");

	MapData newMap;
	newMap.m_uiID = Core::StringToHash32(luaLoader->GetStringByID("ID"));
	newMap.m_uiTileMap = Core::StringToHash32(luaLoader->GetStringByID("TileMap"));

	newMap.m_BackgroundColor.r = luaLoader->GetIntByID("BackgroundR");
	newMap.m_BackgroundColor.g = luaLoader->GetIntByID("BackgroundG");
	newMap.m_BackgroundColor.b = luaLoader->GetIntByID("BackgroundB");
	newMap.m_BackgroundColor.a = luaLoader->GetIntByID("BackgroundA");

	newMap.m_BackgroundRectangle.x = 0;
	newMap.m_BackgroundRectangle.y = 0;
	newMap.m_BackgroundRectangle.w = Core::g_SettingsManager.GetScreenWidth();
	newMap.m_BackgroundRectangle.h = Core::g_SettingsManager.GetScreenHeight();

	m_MapData.insert({ newMap.m_uiID, newMap });

}

}