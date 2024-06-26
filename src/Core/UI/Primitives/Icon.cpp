#include "Icon.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Managers/AssetManager.h"
#include "Core/Systems/Logging.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
Icon::Icon()
        : m_Texture(nullptr)
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 100;
    m_BaseRectangle.h = 100;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    if (m_Texture)
    {
        SDL_RenderCopy(renderer, m_Texture, NULL, &m_BaseRectangle);
    }
    else
    {
        // If no Texture is present, just draw a box.
        SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b,
                               m_Visibility == UIVisibility::eVisible ? m_Color.a : (m_Color.a / 2));
        SDL_RenderFillRect(renderer, &m_BaseRectangle);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::SetTexture(const uint32_t uiTextureId)
{
    Core::TextureAssetData& textureAssetData = Core::g_AssetManager.m_TextureAssetsMap[uiTextureId];
    if (textureAssetData.m_Texture)
    {
        m_Texture = textureAssetData.m_Texture;

        m_BaseRectangle.x = 0;
        m_BaseRectangle.y = 0;
        m_BaseRectangle.w = textureAssetData.m_iWidth;
        m_BaseRectangle.h = textureAssetData.m_iHeight;

        RefreshUI();
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Texture Asset ID does not exist!");
    }
}

}