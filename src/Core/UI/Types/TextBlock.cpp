#include "TextBlock.h"
#include "GameGlobals.h"
#include "Core/Game.h"

#include "Game/Managers/LoadManager.h"
#include "Core/Systems/Systems.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
TextBlock::TextBlock()
    : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_Color = MarkTwo::g_GameGlobals.COLOR_BLACK;
}


// -------------------------------------------------------
// -------------------------------------------------------
TextBlock::~TextBlock()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::Draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, m_MessageTexture, NULL, &m_BaseRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetPosition(int x, int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;
    m_vOffset.m_iX = 0;
    m_vOffset.m_iY = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::RefreshUI()
{
    // Set x-index position based on Anchor.
    switch (m_Anchor.m_Horizontal)
    {
    case HorizontalAlignment::eLeft:
    {
        m_BaseRectangle.x = m_vOffset.m_iX;
        break;
    }
    case HorizontalAlignment::eCenter:
    {
        m_BaseRectangle.x = (MarkTwo::g_GameGlobals.WINDOW_WIDTH / 2) + m_vOffset.m_iX;
        break;
    }
    case HorizontalAlignment::eRight:
    {
        m_BaseRectangle.x = MarkTwo::g_GameGlobals.WINDOW_WIDTH - m_vOffset.m_iX;
        break;
    }
    default:
        break;
    }

    // Set y-index position based on Anchor.
    switch (m_Anchor.m_Vertical)
    {
    case VerticalAlignment::eTop:
    {
        m_BaseRectangle.y = m_vOffset.m_iY;
        break;
    }
    case VerticalAlignment::eCenter:
    {
        m_BaseRectangle.y = (MarkTwo::g_GameGlobals.WINDOW_HEIGHT / 2) + m_vOffset.m_iY;
        break;
    }
    case VerticalAlignment::eBottom:
    {
        m_BaseRectangle.y = MarkTwo::g_GameGlobals.WINDOW_HEIGHT - m_vOffset.m_iY;
        break;
    }
    default:
        break;
    }

    // Set x offset based on Element Alignment.
    switch (m_ElementAlignment.m_Horizontal)
    {
    case HorizontalAlignment::eLeft:
    {
        break;
    }
    case HorizontalAlignment::eCenter:
    {
        m_BaseRectangle.x -= (m_BaseRectangle.w / 2);
        break;
    }
    case HorizontalAlignment::eRight:
    {
        m_BaseRectangle.x -= m_BaseRectangle.w;
        break;
    }
    default:
        break;
    }

    // Set y offset based on Element Alignment.
    switch (m_ElementAlignment.m_Vertical)
    {
    case VerticalAlignment::eTop:
    {
        break;
    }
    case VerticalAlignment::eCenter:
    {
        m_BaseRectangle.y -= (m_BaseRectangle.h / 2);
        break;
    }
    case VerticalAlignment::eBottom:
    {
        m_BaseRectangle.y -= m_BaseRectangle.h;
        break;
    }
    default:
        break;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetText(CoreTypes::String text)
{
    m_Text = text;

    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(MarkTwo::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);

    SDL_Point textureSize;
    SDL_QueryTexture(m_MessageTexture, NULL, NULL, &textureSize.x, &textureSize.y);
    m_BaseRectangle.w = textureSize.x;
    m_BaseRectangle.h = textureSize.y;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetSize(int width, int height)
{
    m_BaseRectangle.w = width;
    m_BaseRectangle.h = height;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetFont(uint32_t fontIDHash)
{
    m_Font = MarkTwo::g_LoadManager.m_FontAssets[fontIDHash].m_Font;
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetColor(SDL_Color color)
{
    m_Color = color;

    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(MarkTwo::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);
}

}