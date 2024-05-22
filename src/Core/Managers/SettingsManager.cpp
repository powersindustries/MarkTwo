#include "SettingsManager.h"

#include "rapidxml_utils.hpp"

#include "Core/Systems/Logging.h"
#include "GameGlobals.h"

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager g_SettingsManager;


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager::SettingsManager()
{
    m_sSettingsFilepath = __PROJECT_DIRECTORY__;
    m_sSettingsFilepath.append("/src/Data/Settings.xml");

    m_SettingsData.m_iWidth = 0;
    m_SettingsData.m_iHeight = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void SettingsManager::Initialize()
{
    rapidxml::file<> xmlFile(m_sSettingsFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* settingsNode = doc.first_node("Settings");
    if (settingsNode)
    {
        m_SettingsData.m_sTitle = settingsNode->first_attribute("Title")->value();
        m_SettingsData.m_iWidth = std::stoi(settingsNode->first_attribute("Width")->value());
        m_SettingsData.m_iHeight = std::stoi(settingsNode->first_attribute("Height")->value());

        m_SettingsData.m_iMusicVolumePercentage = std::stoi(settingsNode->first_attribute("MusicVolume")->value());
        m_SettingsData.m_iFXVolumePercentage = std::stoi(settingsNode->first_attribute("FXVolume")->value());

        Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Settings initialization complete.");
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
int SettingsManager::GetRelativeScreenX(int iX)
{
    return static_cast<int>( (float)(iX * m_SettingsData.m_iWidth) / MarkTwo::g_GameGlobals.BASE_WINDOW_SCALE_WIDTH );
}


// -------------------------------------------------------
// -------------------------------------------------------
int SettingsManager::GetRelativeScreenY(int iY)
{
    return static_cast<int>( (float)(iY * m_SettingsData.m_iHeight) / MarkTwo::g_GameGlobals.BASE_WINDOW_SCALE_HEIGHT );
}

}
