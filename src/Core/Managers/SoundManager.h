#pragma once
#include <string>

namespace Core
{

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void ResetSoundManager();
    void PlaySoundByID(std::string sSoundID);
    void PlayMusicByID(std::string sMusicID);
    void ResumeMusic();
    void PauseMusic();
    void StopAllMusic();

private:

    


};

extern SoundManager g_SoundManager;

}
