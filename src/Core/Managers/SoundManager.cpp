#include "SoundManager.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"
#include "AssetManager.h"

#define DEFAULT_VOLUME 128
#define SOUND_CHANNEL -1

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
SoundManager g_SoundManager;


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::ResetSoundManager()
{
    Mix_HaltMusic();

    int fXVolume = static_cast<int>(DEFAULT_VOLUME * (g_SettingsManager.GetFXVolumePercentage() * 0.01));
    Mix_Volume(SOUND_CHANNEL, fXVolume);

    int musicVolume = static_cast<int>(DEFAULT_VOLUME * (g_SettingsManager.GetMusicVolumePercentage() * 0.01));
    Mix_VolumeMusic(musicVolume);

}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::PlaySoundByID(const std::string& sSoundID)
{
    uint32_t soundHash = Core::StringToHash32(sSoundID);
    SoundAssetData& currSound = g_AssetManager.m_SoundAssetsMap[soundHash];

    Mix_PlayChannel(SOUND_CHANNEL, currSound.m_SoundEffect, 0);
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::PlayMusicByID(const std::string& sMusicID)
{
    if (Mix_PlayingMusic() == 0)
    {
        uint32_t musicHash = Core::StringToHash32(sMusicID);
        MusicAssetData& currMusic = g_AssetManager.m_MusicAssetsMap[musicHash];

        Mix_PlayMusic(currMusic.m_Music, -1);
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::ResumeMusic()
{
    if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::PauseMusic()
{
    Mix_PausedMusic();
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::StopAllMusic()
{
    Mix_HaltMusic();
}

}