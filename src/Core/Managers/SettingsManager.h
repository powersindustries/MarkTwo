#ifndef SettingsManager_h
#define SettingsManager_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

namespace Core
{

struct SettingsData
{
    std::string m_sTitle;
    int m_iWidth;
    int m_iHeight;

    int m_iMusicVolumePercentage;
    int m_iFXVolumePercentage;
};

class SettingsManager
{
public:
    SettingsManager();

    void Initialize();

    std::string GetTitle() const { return m_SettingsData.m_sTitle; }

    int GetScreenWidth() const { return m_SettingsData.m_iWidth; }
    void SetScreenWidth(int width) { m_SettingsData.m_iWidth = width; }

    int GetScreenHeight() const { return m_SettingsData.m_iHeight; }
    void SetScreenHeight(int height) { m_SettingsData.m_iHeight = height; }

    // Get a screen position or length based on the screen's current size.
    int GetRelativeScreenX(int iX);
    int GetRelativeScreenY(int iY);

    int GetMusicVolumePercentage() const { return m_SettingsData.m_iMusicVolumePercentage; };
    int GetFXVolumePercentage() const { return m_SettingsData.m_iFXVolumePercentage; };


private:

    std::string m_sSettingsFilepath;

    SettingsData m_SettingsData;

};

extern SettingsManager g_SettingsManager;
}

#endif