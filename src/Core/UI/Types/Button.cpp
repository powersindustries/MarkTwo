#include "Button.h"
#include "GameGlobals.h"
#include "Core/Game.h"
#include "Core/Managers/LoadManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
Button::Button()
    : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_FontRectangle.x = 0;
    m_FontRectangle.y = 0;
    m_FontRectangle.w = 80;
    m_FontRectangle.h = 15;

    m_LeftClickPressed = false;
    m_RightClickPressed = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
Button::~Button()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::Update(bool leftClicked, bool rightClicked)
{
    int mouseX;
    int mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    if (MouseCollisionDetected(mouseX, mouseY))
    {
        m_LeftClickPressed = leftClicked;
        m_RightClickPressed = rightClicked;
    }
    else
    {
        m_LeftClickPressed = false;
        m_RightClickPressed = false;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 
    MarkTwo::g_GameGlobals.COLOR_BLACK.r, 
    MarkTwo::g_GameGlobals.COLOR_BLACK.g, 
    MarkTwo::g_GameGlobals.COLOR_BLACK.b, 
    MarkTwo::g_GameGlobals.COLOR_BLACK.a);
    SDL_RenderFillRect(renderer, &m_BaseRectangle);

    SDL_RenderCopy(renderer, m_MessageTexture, NULL, &m_FontRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetPosition(int x, int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    m_FontRectangle.x = x;
    m_FontRectangle.y = y;
    
    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;
    m_vOffset.m_iX = 0;
    m_vOffset.m_iY = 0;
    
    RefreshInternalUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetFont(std::string fontID)
{
    m_Font = MarkTwo::g_LoadManager.m_FontAssets[fontID].m_Font;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetSize(int width, int height)
{
    m_BaseRectangle.w = width;
    m_BaseRectangle.h = height;

    RefreshUI();
    RefreshInternalUI();
}

// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetText(std::string text)
{
    m_Text = text;

    RefreshInternalUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetTextAlignment(HorizontalAlignment alignment)
{
    m_TextAlignment = alignment;

    RefreshInternalUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::RefreshUI()
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

    RefreshInternalUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
bool Button::MouseCollisionDetected(int mouseX, int mouseY)
{
    return !((mouseX < m_BaseRectangle.x)
        || (mouseX > m_BaseRectangle.x + m_BaseRectangle.w)
        || (mouseY < m_BaseRectangle.y)
        || (mouseY > m_BaseRectangle.y + m_BaseRectangle.h));
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::RefreshInternalUI()
{
    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), MarkTwo::g_GameGlobals.COLOR_WHITE);

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(MarkTwo::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);

    // Set Texture dimensions
    SDL_Point textureSize;
    SDL_QueryTexture(m_MessageTexture, NULL, NULL, &textureSize.x, &textureSize.y);
    m_FontRectangle.w = textureSize.x;
    m_FontRectangle.h = textureSize.y;

    // Reset Location
    switch (m_TextAlignment)
    {
    case HorizontalAlignment::eLeft:
    {
        m_FontRectangle.x = m_BaseRectangle.x;
        m_FontRectangle.y = m_BaseRectangle.y + ((m_BaseRectangle.h - m_FontRectangle.h) / 2);
        break;
        break;
    }
    case HorizontalAlignment::eCenter:
    {
        m_FontRectangle.x = m_BaseRectangle.x + ((m_BaseRectangle.w - m_FontRectangle.w) / 2);
        m_FontRectangle.y = m_BaseRectangle.y + ((m_BaseRectangle.h - m_FontRectangle.h) / 2);
        break;
    }
    case HorizontalAlignment::eRight:
    {
        m_FontRectangle.x = (m_BaseRectangle.x + m_BaseRectangle.w) - m_FontRectangle.w;
        m_FontRectangle.y = m_BaseRectangle.y + ((m_BaseRectangle.h - m_FontRectangle.h) / 2);
        break;
    }
    }
}

}