#include "Sprite.h"
#include "../Managers/AssetManager.h"

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite()
    : m_Texture(nullptr)
{
    m_uiFrameNumber    = 0;
    m_uiAnimationSpeed = 0;

    m_dRotation = 0.0;

    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = 0;
    m_SourceRectangle.h = 0;

    m_DestinationRectangle.x = 0;
    m_DestinationRectangle.y = 0;
    m_DestinationRectangle.w = 0;
    m_DestinationRectangle.h = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::~Sprite()
{
    free(m_Texture);
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite(uint32_t assetIDHash)
    : m_Texture(nullptr)
{
    m_uiFrameNumber    = 0;
    m_uiAnimationSpeed = 0;

    m_dRotation = 0.0;

    SetTexture(assetIDHash);

    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = 0;
    m_SourceRectangle.h = 0;

    m_DestinationRectangle.x = 0;
    m_DestinationRectangle.y = 0;
    m_DestinationRectangle.w = 0;
    m_DestinationRectangle.h = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite(uint32_t assetIDHash, uint8_t animationSpeed)
{
    SetTexture(assetIDHash);

    m_uiAnimationSpeed = animationSpeed;

    m_dRotation = 0.0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Update(const float deltaTime)
{
    if (m_uiFrameNumber > 0)
    {
        m_SourceRectangle.y = m_SourceRectangle.h * static_cast<int>(SDL_GetTicks() / m_uiAnimationSpeed % m_uiFrameNumber);
    }

    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Update(const float deltaTime, SDL_Rect& rectangle)
{
    m_Transform.SetTransform(rectangle);

    if (m_uiFrameNumber > 0)
    {
        m_SourceRectangle.y = m_SourceRectangle.h * static_cast<int>(SDL_GetTicks() / m_uiAnimationSpeed % m_uiFrameNumber);
    }

    // Update Destination Rectangle.
    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Draw(SDL_Renderer* renderer, const SDL_RendererFlip& flip)
{
	SDL_RenderCopyEx(renderer, m_Texture, &m_SourceRectangle, &m_DestinationRectangle, m_dRotation, NULL, flip);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::SetTexture(const uint32_t textureIDHash)
{
    Core::TextureAssetData& textureAssetData = Core::g_AssetManager.m_TextureAssetsMap[textureIDHash];
    m_Texture = textureAssetData.m_Texture;
    m_uiFrameNumber = textureAssetData.m_uiFrames;
    
    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = textureAssetData.m_iWidth;
    m_SourceRectangle.h = m_uiFrameNumber == 0 ? textureAssetData.m_iHeight : textureAssetData.m_iHeight / m_uiFrameNumber;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::SetRotation(const double degrees)
{
    m_dRotation = degrees;
}

}
