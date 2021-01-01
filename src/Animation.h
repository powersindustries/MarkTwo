#pragma once


namespace MarkTwo
{
    namespace GameCore
    {
        class Animation
        {
        public:
            Animation();
            Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);


            unsigned int m_uiIndex;
            unsigned int m_uiFrameNumbers;
            unsigned int m_uiAnimationSpeed;
        };
    }
}
