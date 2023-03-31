#include "SettingsManager.h"
#include "Core/Systems/Logging.h"
#include "GameGlobals.h"
#include "../Types/LuaTableLoader.h"

namespace CoreManagers
{


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager g_SettingsManager;


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager::SettingsManager()
    : m_MainWindow(nullptr)
{
    m_sSettingsFilepath.append(__PROJECT_DIRECTORY__);
    m_sSettingsFilepath.append("/src/Data/Settings.lua");

    m_SettingsData.m_iWidth = 0;
    m_SettingsData.m_iHeight = 0;

}


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager::~SettingsManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void SettingsManager::InitializeSettings()
{
	CoreTypes::LuaTableLoader* luaLoader = new CoreTypes::LuaTableLoader(m_sSettingsFilepath);
	luaLoader->LoadTableByID("Settings");

    m_SettingsData.m_sTitle = luaLoader->GetStringByID("Title");
    m_SettingsData.m_iWidth = luaLoader->GetIntByID("Width");
    m_SettingsData.m_iHeight = luaLoader->GetIntByID("Height");

    m_SettingsData.m_iMusicVolumePercentage = luaLoader->GetIntByID("MusicVolume");
    m_SettingsData.m_iFXVolumePercentage = luaLoader->GetIntByID("FXVolume");

	delete luaLoader;


    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Settings initialization complete.");
}


// -------------------------------------------------------
// -------------------------------------------------------
int SettingsManager::GetRelativeScreenX(int iX)
{
    const float fOutputX = (float)(iX * m_SettingsData.m_iWidth) / MarkTwo::g_GameGlobals.BASE_WINDOW_SCALE_WIDTH;
    return static_cast<int>(fOutputX);
}


// -------------------------------------------------------
// -------------------------------------------------------
int SettingsManager::GetRelativeScreenY(int iY)
{
    const float fOutputY = (float)(iY * m_SettingsData.m_iHeight) / MarkTwo::g_GameGlobals.BASE_WINDOW_SCALE_HEIGHT;
    return static_cast<int>(fOutputY);
}

}
