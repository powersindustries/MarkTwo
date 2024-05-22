#include "Texture.h"
#include "../Systems/Systems.h"
#include "../Managers/AssetManager.h"
#include "GameGlobals.h"

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
Texture::Texture()
	: m_Texture(nullptr)
{
	m_BaseRectangle.x = 0;
	m_BaseRectangle.y = 0;
	m_BaseRectangle.w = 100;
	m_BaseRectangle.h = 100;

	m_Color = MarkTwo::g_GameGlobals.COLOR_RED;
}


// -------------------------------------------------------
// -------------------------------------------------------
Texture::Texture(uint32_t uiAssetId)
{
	SetTexture(uiAssetId);

	m_Color = MarkTwo::g_GameGlobals.COLOR_RED;
}


// -------------------------------------------------------
// -------------------------------------------------------
Texture::~Texture()
{
	free(m_Texture);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Texture::Draw(SDL_Renderer* renderer)
{
	if (m_Texture)
	{
		SDL_RenderCopy(renderer, m_Texture, NULL, &m_BaseRectangle);
	}
	else
	{
		// If no Texture is present, just draw a box.
		SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
		SDL_RenderFillRect(renderer, &m_BaseRectangle);
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
void Texture::SetTexture(const uint32_t uiTextureID)
{
	Core::TextureAssetData& textureAssetData = Core::g_AssetManager.m_TextureAssetsMap[uiTextureID];
	if (textureAssetData.m_Texture)
	{
		m_Texture = textureAssetData.m_Texture;

		m_BaseRectangle.x = 0;
		m_BaseRectangle.y = 0;
		m_BaseRectangle.w = textureAssetData.m_iWidth;
		m_BaseRectangle.h = textureAssetData.m_iHeight;

	}
	else
	{
		Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "Texture Asset ID does not exist!");
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
void Texture::SetSize(const int w, const int h)
{
	m_BaseRectangle.w = w;
	m_BaseRectangle.h = h;
}


void Texture::SetPosition(const int x, const int y)
{
	m_BaseRectangle.x = x;
	m_BaseRectangle.y = y;
}
}
