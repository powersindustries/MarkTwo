#include "AssetManager.h"
#include <cstdint>
#include <string>

#include "rapidxml_utils.hpp"

#include "GameGlobals.h"
#include "../Systems/Hash.h"
#include "../Systems/Logging.h"

#define DEFAULT_FONT_SIZE 24

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
AssetManager g_AssetManager;


// -------------------------------------------------------
// -------------------------------------------------------
AssetManager::AssetManager()
{
    m_sManifestFilepath.append(__PROJECT_DIRECTORY__);
    m_sManifestFilepath.append("/src/Data/AssetManifest.xml");

    m_sTextureDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sTextureDirectorypath.append("/src/Assets/Textures/");

    m_sFontsDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sFontsDirectorypath.append("/src/Assets/Fonts/");

    m_sSoundsDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sSoundsDirectorypath.append("/src/Assets/Sounds/");

    m_sSaveDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sSaveDirectorypath.append("/src/Data/Save.xml");
}


// -------------------------------------------------------
// -------------------------------------------------------
AssetManager::~AssetManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::Initialize(SDL_Renderer* renderer)
{
    LoadTextureAssets(renderer);
    LoadTileMapAssets();
    LoadFontAssets(renderer);
    LoadSoundAssets();
    LoadMusicAssets();
}


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Surface* AssetManager::GetAssetSurfaceByID(std::string AssetID)
{
    TextureAssetData& iconTextureData = m_TextureAssets[Core::StringToHash32(AssetID)];
    std::string sAssetPath = m_sTextureDirectorypath + iconTextureData.m_File;
    return IMG_Load(sAssetPath.c_str());
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadTextureAssets(SDL_Renderer* renderer)
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* texturesNode = doc.first_node()->first_node("Textures");
    if (texturesNode)
    {
        for (rapidxml::xml_node<>* child = texturesNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in LoadTextureAssets method is nullptr.");
                continue;
            }

            TextureAssetData textureAssetData;
            textureAssetData.m_uiID = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            textureAssetData.m_File = child->first_attribute("File")->value();

            rapidxml::xml_attribute<>* framesAttribute = child->first_attribute("Frames");
            if (framesAttribute)
            {
                textureAssetData.m_uiFrames = std::stoi(framesAttribute->value());
            }
            else
            {
                textureAssetData.m_uiFrames = 0;
            }

            std::string sAssetPath = m_sTextureDirectorypath;
            sAssetPath.append(textureAssetData.m_File);

            SDL_Surface* surface = IMG_Load(sAssetPath.c_str());
            textureAssetData.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            SDL_QueryTexture(textureAssetData.m_Texture, NULL, NULL, &textureAssetData.m_iWidth, &textureAssetData.m_iHeight);

            m_TextureAssets[textureAssetData.m_uiID] = textureAssetData;
        }
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Texture assets loaded.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadTileMapAssets()
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* mapNode = doc.first_node()->first_node("TileMaps");
    if (mapNode)
    {
        for (rapidxml::xml_node<>* child = mapNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in LoadTileMapAssets method is nullptr.");
                continue;
            }

            TileMapAssetData newTileMap;
            newTileMap.m_uiID = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            newTileMap.m_TextureAssetData = &m_TextureAssets[newTileMap.m_uiID];
            newTileMap.m_uiLength = newTileMap.m_TextureAssetData->m_iWidth / MarkTwo::g_GameGlobals.TILE_SIZE;

            uint8_t uiRow = 0;
            const uint8_t tilemapSize = newTileMap.m_uiLength * newTileMap.m_uiLength;
            for (uint8_t x = 0; x < tilemapSize; ++x)
            {
                // Calculate current row.
                if ((x != 0) && (x % newTileMap.m_uiLength == 0))
                {
                    uiRow++;
                }

                SDL_Rect newRect;
                newRect.x = (x - (uiRow * newTileMap.m_uiLength)) * MarkTwo::g_GameGlobals.TILE_SIZE;
                newRect.y = uiRow * MarkTwo::g_GameGlobals.TILE_SIZE;

                newRect.w = MarkTwo::g_GameGlobals.TILE_SIZE;
                newRect.h = MarkTwo::g_GameGlobals.TILE_SIZE;

                newTileMap.m_SourceRectangles.push_back(newRect);
            }

            m_TileMapAssets.insert({ newTileMap.m_uiID, newTileMap });
        }
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Tile map assets loaded.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadFontAssets(SDL_Renderer* renderer)
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* fontNode = doc.first_node()->first_node("Fonts");
    if (fontNode)
    {
        for (rapidxml::xml_node<>* child = fontNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in LoadFontAssets method is nullptr.");
                continue;
            }

            FontAssetData fontAssetData;
            fontAssetData.m_uiID = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            fontAssetData.m_File = child->first_attribute("File")->value();

            std::string assetPath = m_sFontsDirectorypath;
            assetPath.append(fontAssetData.m_File);

            fontAssetData.m_Font = TTF_OpenFont(assetPath.c_str(), DEFAULT_FONT_SIZE);

            m_FontAssets[fontAssetData.m_uiID] = fontAssetData;
        }
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Font assets loaded.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadSoundAssets()
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* soundNode = doc.first_node()->first_node("Sounds");
    if (soundNode)
    {
        for (rapidxml::xml_node<>* child = soundNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in LoadSoundAssets method is nullptr.");
                continue;
            }

            SoundAssetData soundAssetData;
            soundAssetData.m_uiID = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            soundAssetData.m_File = child->first_attribute("File")->value();

            std::string assetPath = m_sSoundsDirectorypath;
            assetPath.append(soundAssetData.m_File);

            soundAssetData.m_SoundEffect = Mix_LoadWAV(assetPath.c_str());

            if (soundAssetData.m_SoundEffect)
            {
                m_SoundAssets[soundAssetData.m_uiID] = soundAssetData;
            }
            else
            {
                std::string errorMessage = "Sound asset unable to load: ";
                errorMessage.append(child->first_attribute("ID")->value());

                Core::SYSTEMS_LOG(Core::LoggingLevel::eError, child->first_attribute("ID")->value());
            }
        }
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Sound assets loaded");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadMusicAssets()
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* musicNode = doc.first_node()->first_node("Music");
    if (musicNode)
    {
        for (rapidxml::xml_node<>* child = musicNode->first_node(); child; child = child->next_sibling())
        {
            if (!child)
            {
                Core::SYSTEMS_LOG(Core::LoggingLevel::eWarning, "Child node in LoadMusicAssets method is nullptr.");
                continue;
            }

            MusicAssetData musicAssetData;
            musicAssetData.m_uiID = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            musicAssetData.m_File = child->first_attribute("File")->value();

            std::string assetPath = m_sSoundsDirectorypath;
            assetPath.append(musicAssetData.m_File);

            musicAssetData.m_Music = Mix_LoadMUS(assetPath.c_str());

            if (musicAssetData.m_Music)
            {
                m_MusicAssets[musicAssetData.m_uiID] = musicAssetData;
            }
            else
            {
                std::string errorMessage = "Music asset unable to load: ";
                errorMessage.append(child->first_attribute("ID")->value());

                Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage.c_str());
            }
        }
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Music assets loaded.");
}

}
