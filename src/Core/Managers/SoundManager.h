#ifndef SoundManager_h
#define SoundManager_h

#include <string>

namespace Core
{

class SoundManager
{
public:

    void ResetSoundManager();
    void PlaySoundById(const std::string& soundId);
    void PlayMusicById(const std::string& musicId);
    void ResumeMusic();
    void PauseMusic();
    void StopAllMusic();


};

extern SoundManager g_SoundManager;

}

#endif