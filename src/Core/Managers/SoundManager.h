#ifndef SoundManager_h
#define SoundManager_h

#include <string>

namespace Core
{

class SoundManager
{
public:

    void ResetSoundManager();
    void PlaySoundByID(const std::string& sSoundID);
    void PlayMusicByID(const std::string& sMusicID);
    void ResumeMusic();
    void PauseMusic();
    void StopAllMusic();


};

extern SoundManager g_SoundManager;

}

#endif