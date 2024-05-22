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
    m_sManifestFilepath = __PROJECT_DIRECTORY__;
    m_sManifestFilepath.append("/src/Data/AssetManifest.xml");

    m_sTextureDirectoryPath = __PROJECT_DIRECTORY__;
    m_sTextureDirectoryPath.append("/src/Assets/Textures/");

    m_sFontsDirectoryPath = __PROJECT_DIRECTORY__;
    m_sFontsDirectoryPath.append("/src/Assets/Fonts/");

    m_sSoundsDirectoryPath = __PROJECT_DIRECTORY__;
    m_sSoundsDirectoryPath.append("/src/Assets/Sounds/");

    m_sSaveDirectoryPath = __PROJECT_DIRECTORY__;
    m_sSaveDirectoryPath.append("/src/Data/Save.xml");
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
SDL_Surface* AssetManager::GetAssetSurfaceById(const std::string& assetId)
{
    const TextureAssetData& iconTextureData = m_TextureAssetsMap[Core::StringToHash32(assetId)];
    const std::string assetPath = m_sTextureDirectoryPath + iconTextureData.m_sFile;

    return IMG_Load(assetPath.c_str());
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
            textureAssetData.m_uiId = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            textureAssetData.m_sFile = child->first_attribute("File")->value();

            rapidxml::xml_attribute<>* framesAttribute = child->first_attribute("Frames");
            if (framesAttribute)
            {
                textureAssetData.m_uiFrames = std::stoi(framesAttribute->value());
            }
            else
            {
                textureAssetData.m_uiFrames = 0;
            }

            std::string assetPath = m_sTextureDirectoryPath;
            assetPath.append(textureAssetData.m_sFile);

            SDL_Surface* surface = IMG_Load(assetPath.c_str());
            textureAssetData.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            SDL_QueryTexture(textureAssetData.m_Texture, NULL, NULL, &textureAssetData.m_iWidth, &textureAssetData.m_iHeight);

            m_TextureAssetsMap[textureAssetData.m_uiId] = textureAssetData;
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
            newTileMap.m_uiId = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            newTileMap.m_TextureAssetData = &m_TextureAssetsMap[newTileMap.m_uiId];
            newTileMap.m_uiLength = newTileMap.m_TextureAssetData->m_iWidth / MarkTwo::g_GameGlobals.TILE_SIZE;

            uint8_t row = 0;
            const uint8_t tilemapSize = newTileMap.m_uiLength * newTileMap.m_uiLength;
            for (uint8_t x = 0; x < tilemapSize; ++x)
            {
                // Calculate current row.
                if ((x != 0) && (x % newTileMap.m_uiLength == 0))
                {
                    row++;
                }

                SDL_Rect newRect;
                newRect.x = (x - (row * newTileMap.m_uiLength)) * MarkTwo::g_GameGlobals.TILE_SIZE;
                newRect.y = row * MarkTwo::g_GameGlobals.TILE_SIZE;

                newRect.w = MarkTwo::g_GameGlobals.TILE_SIZE;
                newRect.h = MarkTwo::g_GameGlobals.TILE_SIZE;

                newTileMap.m_SourceRectangles.push_back(newRect);
            }

            m_TileMapAssetsMap.insert({newTileMap.m_uiId, newTileMap });
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
            fontAssetData.m_uiId = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            fontAssetData.m_sFile = child->first_attribute("File")->value();

            std::string assetPath = m_sFontsDirectoryPath;
            assetPath.append(fontAssetData.m_sFile);

            fontAssetData.m_Font = TTF_OpenFont(assetPath.c_str(), DEFAULT_FONT_SIZE);

            m_FontAssetsMap[fontAssetData.m_uiId] = fontAssetData;
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
            soundAssetData.m_uiId = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            soundAssetData.m_sFile = child->first_attribute("File")->value();

            std::string assetPath = m_sSoundsDirectoryPath;
            assetPath.append(soundAssetData.m_sFile);

            soundAssetData.m_SoundEffect = Mix_LoadWAV(assetPath.c_str());

            if (soundAssetData.m_SoundEffect)
            {
                m_SoundAssetsMap[soundAssetData.m_uiId] = soundAssetData;
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
            musicAssetData.m_uiId = Core::StringToHash32(std::string(child->first_attribute("ID")->value()));
            musicAssetData.m_sFile = child->first_attribute("File")->value();

            std::string assetPath = m_sSoundsDirectoryPath;
            assetPath.append(musicAssetData.m_sFile);

            musicAssetData.m_Music = Mix_LoadMUS(assetPath.c_str());

            if (musicAssetData.m_Music)
            {
                m_MusicAssetsMap[musicAssetData.m_uiId] = musicAssetData;
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
