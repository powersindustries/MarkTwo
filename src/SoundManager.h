#pragma once
#include "Game.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class SoundManager
        {
        public:
            void PlaySound(const char* soundFilePath);
            
        };

        extern SoundManager g_SoundManager;
    }
}
