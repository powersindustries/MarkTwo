#include "Animation.h"


namespace MarkTwo
{
    namespace GameCore
    {
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Animation::Animation()
        {
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Animation::Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed)
        {
            m_uiIndex = index;
            m_uiFrameNumbers = numFrames;
            m_uiAnimationSpeed = animationSpeed;
        }

    }
}
