#include "TextBlock.h"
#include "GameGlobals.h"
#include "Core/Game.h"
#include "Core/Managers/LoadManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
TextBlock::TextBlock()
    : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;

    m_ElementAlignment.m_Horizontal =  HorizontalAlignment::eLeft; 
    m_ElementAlignment.m_Vertical = VerticalAlignment::eTop;

    m_Offset.m_iX = 0;
    m_Offset.m_iY = 0;

    m_BaseRectangle.x = 10;
    m_BaseRectangle.y = 10;
    m_BaseRectangle.w = 100;
    m_BaseRectangle.h = 25;

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
void TextBlock::Update(bool leftClicked, bool rightClicked)
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
void TextBlock::SetAnchor(HorizontalAlignment horizontal, VerticalAlignment vertical)
{
    m_Anchor.m_Horizontal = horizontal;
    m_Anchor.m_Vertical = vertical;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetElementAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical)
{
    m_ElementAlignment.m_Horizontal = horizontal;
    m_ElementAlignment.m_Vertical = vertical;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetOffset(int xOffset, int yOffset)
{
    m_Offset.m_iX = xOffset;
    m_Offset.m_iY = yOffset;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetPosition(int x, int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;
    m_Offset.m_iX = 0;
    m_Offset.m_iY = 0;
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
        m_BaseRectangle.x = m_Offset.m_iX;
        break;
    }
    case HorizontalAlignment::eCenter:
    {
        m_BaseRectangle.x = (MarkTwo::g_GameGlobals.WINDOW_WIDTH / 2) + m_Offset.m_iX;
        break;
    }
    case HorizontalAlignment::eRight:
    {
        m_BaseRectangle.x = MarkTwo::g_GameGlobals.WINDOW_WIDTH - m_Offset.m_iX;
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
        m_BaseRectangle.y = m_Offset.m_iY;
        break;
    }
    case VerticalAlignment::eCenter:
    {
        m_BaseRectangle.y = (MarkTwo::g_GameGlobals.WINDOW_HEIGHT / 2) + m_Offset.m_iY;
        break;
    }
    case VerticalAlignment::eBottom:
    {
        m_BaseRectangle.y = MarkTwo::g_GameGlobals.WINDOW_HEIGHT - m_Offset.m_iY;
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
void TextBlock::SetText(std::string text)
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
void TextBlock::SetFont(std::string fontID)
{
    m_Font = MarkTwo::g_LoadManager.m_FontAssets[fontID].m_Font;
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


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetWidth(int width)
{
    m_BaseRectangle.w = width;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetHeight(int height)
{
    m_BaseRectangle.h = height;

    RefreshUI();
}

}