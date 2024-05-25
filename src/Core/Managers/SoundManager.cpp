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
void SoundManager::PlaySoundById(const std::string& soundId)
{
    const uint8_t soundHash = Core::StringToHash(soundId);
    SoundAssetData& currSound = g_AssetManager.m_SoundAssetsMap[soundHash];

    Mix_PlayChannel(SOUND_CHANNEL, currSound.m_SoundEffect, 0);
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::PlayMusicById(const std::string& musicId)
{
    if (Mix_PlayingMusic() == 0)
    {
        const uint8_t musicHash = Core::StringToHash(musicId);
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