#include "LoadManager.h"
#include <iostream>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#include "GameGlobals.h"
#include "Core/Systems/Systems.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
LoadManager g_LoadManager;


// -------------------------------------------------------
// -------------------------------------------------------
LoadManager::LoadManager()
{
    m_sManifestFilepath.append(__PROJECT_DIRECTORY__);
    m_sManifestFilepath.append("/src/Data/AssetManifest.xml");

    m_sTextureDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sTextureDirectorypath.append("/src/Assets/Textures/");

    m_sFontsDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sFontsDirectorypath.append("/src/Assets/Fonts/");
}


// -------------------------------------------------------
// -------------------------------------------------------
LoadManager::~LoadManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void LoadManager::InitialLoad(SDL_Renderer* renderer)
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    // Parse Texture Data
    rapidxml::xml_node<>* texturesNode = doc.first_node()->first_node("Textures");
    for (rapidxml::xml_node<>* child = texturesNode->first_node(); child; child = child->next_sibling())
    {
        TextureAssetData textureAssetData;
        textureAssetData.m_ID = child->first_attribute("ID")->value();
        textureAssetData.m_File = child->first_attribute("File")->value();

        CoreTypes::String assetPath = m_sTextureDirectorypath;
        assetPath.append(textureAssetData.m_File);
        SDL_Surface* surface = IMG_Load(assetPath.c_str());
        textureAssetData.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_QueryTexture(textureAssetData.m_Texture, NULL, NULL, &textureAssetData.m_TextureWidth, &textureAssetData.m_TextureHeight);

        m_TextureAssets[CoreSystems::StringToHash32(textureAssetData.m_ID)] = textureAssetData;
    }

    // Parse Font Data
    rapidxml::xml_node<>* fontNode = doc.first_node()->first_node("Fonts");
    for (rapidxml::xml_node<>* child = fontNode->first_node(); child; child = child->next_sibling())
    {
        FontAssetData fontAssetData;
        fontAssetData.m_ID = child->first_attribute("ID")->value();
        fontAssetData.m_File = child->first_attribute("File")->value();

        CoreTypes::String assetPath = m_sFontsDirectorypath;
        assetPath.append(fontAssetData.m_File);
        int fontsize = 24;
        fontAssetData.m_Font = TTF_OpenFont(assetPath.c_str(), fontsize);

        m_FontAssets[CoreSystems::StringToHash32(fontAssetData.m_ID)] = fontAssetData;
    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Initial LoadManager Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void LoadManager::Update(float* deltaTime)
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void LoadManager::Draw(SDL_Renderer* renderer)
{
}

}