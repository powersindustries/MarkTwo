#include "Sprite.h"
#include "../Managers/LoadManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite()
    : m_Texture(nullptr)
{
    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = 0;
    m_SourceRectangle.h = 0;

    m_DestinationRectangle.x = 0;
    m_DestinationRectangle.y = 0;
    m_DestinationRectangle.w = 0;
    m_DestinationRectangle.h = 0;

    m_bIsAnimated = true;
    m_iFrameNumber = 0;
    m_iAnimationSpeed = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::~Sprite()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite(std::string assetID)
{
    m_bIsAnimated = false;

    SetTexture(assetID);
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite(std::string assetID, int numFrames, int animationSpeed, bool hasDirection)
{
    m_bIsAnimated = true;
    m_iFrameNumber = numFrames;
    m_iAnimationSpeed = animationSpeed;

    if (hasDirection)
    {
        AnimationData up = AnimationData(0, numFrames, animationSpeed);
        AnimationData down = AnimationData(1, numFrames, animationSpeed);
        AnimationData left = AnimationData(2, numFrames, animationSpeed);
        AnimationData right = AnimationData(3, numFrames, animationSpeed);

        m_Animations.emplace("up", up);
        m_Animations.emplace("down", down);
        m_Animations.emplace("left", left);
        m_Animations.emplace("right", right);

        m_uiAnimationIndex = 0;
        m_sCurrentAnimationName = "up";
    }
    else
    {
        std::string single = "single";
        AnimationData singleAnimation = AnimationData(0, numFrames, animationSpeed);
        m_Animations.emplace(single, singleAnimation);
        m_uiAnimationIndex = 0;
        m_sCurrentAnimationName = single;
    }

    Play(m_sCurrentAnimationName);
    SetTexture(assetID);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::InitializeSprite(SDL_Rect& inRectangle)
{
    m_Transform.SetTransform(inRectangle);

    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = m_Transform.m_iWidth;
    m_SourceRectangle.h = m_Transform.m_iHeight;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::InitializeSprite(int x, int y, int width, int height)
{
    m_Transform.SetTransform(x, y, width, height);

    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = m_Transform.m_iWidth;
    m_SourceRectangle.h = m_Transform.m_iHeight;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Update(float deltaTime)
{
    // Update Source Rectangle
    if (m_bIsAnimated)
    {
        m_SourceRectangle.x = m_SourceRectangle.w * static_cast<int>(SDL_GetTicks() / m_iAnimationSpeed % m_iFrameNumber);
    }

    m_SourceRectangle.y = m_uiAnimationIndex * m_Transform.m_iHeight;

    // Update Destination Rectangle
    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Update(float deltaTime, SDL_Rect& inRectangle)
{
    // Update Transform Data
    m_Transform.SetTransform(inRectangle);

    // Update Source Rectangle
    if (m_bIsAnimated)
    {
        m_SourceRectangle.x = m_SourceRectangle.w * static_cast<int>(SDL_GetTicks() / m_iAnimationSpeed % m_iFrameNumber);
    }

    m_SourceRectangle.y = m_uiAnimationIndex * m_Transform.m_iHeight;

    // Update Destination Rectangle
    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Update(float deltaTime, Transform& inTransform)
{
    // Update Transform Data
    m_Transform = inTransform;

    // Update Source Rectangle
    if (m_bIsAnimated)
    {
        m_SourceRectangle.x = m_SourceRectangle.w * static_cast<int>(SDL_GetTicks() / m_iAnimationSpeed % m_iFrameNumber);
    }

    m_SourceRectangle.y = m_uiAnimationIndex * m_Transform.m_iHeight;

    // Update Destination Rectangle
    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, m_Texture, &m_SourceRectangle, &m_DestinationRectangle, 0.0, NULL, SDL_FLIP_NONE);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Play(std::string animationName)
{
    m_iFrameNumber = m_Animations[animationName].m_uiFrameCount;
    m_uiAnimationIndex = m_Animations[animationName].m_uiIndex;
    m_iAnimationSpeed = m_Animations[animationName].m_uiAnimationSpeed;
    m_sCurrentAnimationName = animationName;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::SetTexture(std::string textureID)
{
    m_Texture = g_LoadManager.m_TextureAssets[textureID].m_Texture;
}

}