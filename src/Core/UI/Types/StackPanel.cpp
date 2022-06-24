#include "StackPanel.h"
#include "GameGlobals.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
StackPanel::StackPanel()
{
    m_iPadding = 0;

    m_Alignment = StackpanelAlignment::eVertical;
}


// -------------------------------------------------------
// -------------------------------------------------------
StackPanel::~StackPanel()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::Draw(SDL_Renderer* renderer)
{
    int childCount = (int)m_Children.size();
    for (int x = 0; x < childCount; ++x)
    {
        m_Children[x]->Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetPosition(int x, int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    ResizeSpacing();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::RefreshUI()
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

    ResizeSpacing();
}

// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::AddChild(UIBase* child)
{
    m_Children.push_back(child);

    ResizeSpacing();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetChildAlignment(StackpanelAlignment alignment)
{
    m_Alignment = alignment;

    ResizeSpacing();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetPadding(int padding)
{
    m_iPadding = padding;

    ResizeSpacing();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::ResizeSpacing()
{
    // Reset StackWidth and StackHeight
    m_BaseRectangle.w = 0;
    m_BaseRectangle.h = 0;

    // Reset position of all children based on m_Alignment
    int childCount = (int)m_Children.size();
    for (int x = 0; x < childCount; ++x)
    {
        UIBase* currentChild = m_Children[x];
        if (m_Alignment == StackpanelAlignment::eVertical)
        {
            // Set child Position
            int newY = m_BaseRectangle.y + m_BaseRectangle.h + m_iPadding;
            currentChild->SetPosition(m_BaseRectangle.x, newY);

            // Set Stack Width and Height
            if (m_BaseRectangle.w < currentChild->GetWidth())
            {
                m_BaseRectangle.w = currentChild->GetWidth();
            }

            m_BaseRectangle.h += currentChild->GetHeight() + m_iPadding;
        }
        else
        {
            // Set child Position
            int newX = m_BaseRectangle.x + m_BaseRectangle.w + m_iPadding;
            currentChild->SetPosition(newX, m_BaseRectangle.y);

            // Set Stack Width and Height
            if (m_BaseRectangle.h < currentChild->GetHeight())
            {
                m_BaseRectangle.h = currentChild->GetHeight();
            }

            m_BaseRectangle.w += currentChild->GetWidth() + m_iPadding;
        }
    }
}

}