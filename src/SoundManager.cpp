#include "SoundManager.h"

namespace MarkTwo
{
    namespace GameCore
    {
        SoundManager g_SoundManager;


        // ---------------------------------------------------------------------
        // link to reference:  https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/
        // ---------------------------------------------------------------------
        void SoundManager::PlaySound(const char* soundFilePath)
        {
            SDL_AudioSpec wavSpec;
            Uint32 wavLength;
            Uint8* wavBuffer;
            SDL_LoadWAV(soundFilePath, &wavSpec, &wavBuffer, &wavLength);
            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
            int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
            SDL_PauseAudioDevice(deviceId, 0);
        }

    }
}
