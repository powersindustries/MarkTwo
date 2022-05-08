#include "Box.h"
#include "GameGlobals.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
Box::Box()
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 10;
    m_BaseRectangle.h = 10;

    m_Anchor.m_Horizontal  = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical    = VerticalAlignment::eTop;

    m_ElementAlignment.m_Horizontal = HorizontalAlignment::eLeft;
    m_ElementAlignment.m_Vertical = VerticalAlignment::eTop;

    m_Offset.m_iX = 0;
    m_Offset.m_iY = 0;

    m_Color = MarkTwo::g_GameGlobals.COLOR_RED;
}


// -------------------------------------------------------
// -------------------------------------------------------
Box::~Box()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::Update(bool leftClicked, bool rightClicked)
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
    SDL_RenderFillRect(renderer, &m_BaseRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetAnchor(HorizontalAlignment horizontal, VerticalAlignment vertical)
{
    m_Anchor.m_Horizontal = horizontal;
    m_Anchor.m_Vertical   = vertical;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetElementAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical)
{
    m_ElementAlignment.m_Horizontal = horizontal;
    m_ElementAlignment.m_Vertical = vertical;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetPosition(int x, int y)
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
void Box::SetOffset(int xOffset, int yOffset)
{
    m_Offset.m_iX = xOffset;
    m_Offset.m_iY = yOffset;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::RefreshUI()
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
void Box::SetSize(int width, int height)
{
    m_BaseRectangle.w = width;
    m_BaseRectangle.h = height;

    RefreshUI();
}

}