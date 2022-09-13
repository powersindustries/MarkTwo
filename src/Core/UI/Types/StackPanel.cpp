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

    RefreshUI();

    //ResizeSpacing();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::RefreshUI()
{
    // Set Anchor position.
    int leftX   = 0;
    int centerX = MarkTwo::g_GameGlobals.WINDOW_WIDTH / 2;
    int rightX  = MarkTwo::g_GameGlobals.WINDOW_WIDTH;

    int topY     = 0;
    int middleY  = MarkTwo::g_GameGlobals.WINDOW_HEIGHT / 2;
    int Bottom1Y = MarkTwo::g_GameGlobals.WINDOW_HEIGHT;

    // Check to see if the position is an anchored position. If it is, reset m_BaseRectangle.
    bool bAnchoredPosition = (
        (m_BaseRectangle.x == leftX && m_BaseRectangle.y == topY) ||
        (m_BaseRectangle.x == leftX && m_BaseRectangle.y == middleY) ||
        (m_BaseRectangle.x == leftX && m_BaseRectangle.y == Bottom1Y) ||

        (m_BaseRectangle.x == centerX && m_BaseRectangle.y == topY) ||
        (m_BaseRectangle.x == centerX && m_BaseRectangle.y == middleY) ||
        (m_BaseRectangle.x == centerX && m_BaseRectangle.y == Bottom1Y) ||

        (m_BaseRectangle.x == rightX && m_BaseRectangle.y == topY) ||
        (m_BaseRectangle.x == rightX && m_BaseRectangle.y == middleY) ||
        (m_BaseRectangle.x == rightX && m_BaseRectangle.y == Bottom1Y));


    // If not unique, set m_BaseRectangle position to be an anchor point.
    if (bAnchoredPosition)
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
    }


    const uint8_t uiChildCount = static_cast<uint8_t>(m_Children.size());

    // Get the width and height values for the stack.
    int iStackWidth  = 0;
    int iStackHeight = 0;
    for (int x = 0; x < uiChildCount; ++x)
    {
        UIBase* currentChild = m_Children[x];
        if (m_Alignment == StackpanelAlignment::eVertical)
        {
            if (currentChild->GetWidth() > iStackWidth)
            {
                iStackWidth = currentChild->GetWidth();
            }

            iStackHeight += currentChild->GetHeight() + m_iPadding;
        }
        else
        {
            iStackWidth += currentChild->GetWidth() + m_iPadding;

            if (currentChild->GetHeight() > iStackHeight)
            {
                iStackHeight = currentChild->GetHeight();
            }
        }
    }

    // Offset m_BaseRectangle position based on m_ElementAlignment.
    switch (m_ElementAlignment.m_Horizontal)
    {
    case HorizontalAlignment::eLeft: 
    {
        break;
    }
    case HorizontalAlignment::eCenter: 
    {
        m_BaseRectangle.x = m_BaseRectangle.x - (iStackWidth / 4);
        break;
    }
    case HorizontalAlignment::eRight: 
    {
        m_BaseRectangle.x = m_BaseRectangle.x - (iStackWidth / 2);
        break;
    }
    default: 
    {
        break;
    }
    }

    switch (m_ElementAlignment.m_Vertical)
    {
    case VerticalAlignment::eTop: 
    {
        break;
    }
    case VerticalAlignment::eCenter: 
    {
        m_BaseRectangle.y = m_BaseRectangle.y - (iStackHeight / 4);
        break;
    }
    case VerticalAlignment::eBottom: 
    {
        m_BaseRectangle.y = m_BaseRectangle.y - (iStackHeight / 2);
        break;
    }
    default: 
    {
        break;
    }
    }

    // Set children positions.
    for (int x = 0; x < uiChildCount; ++x)
    {
        UIBase* currentChild = m_Children[x];

        if (x == 0)
        {
            if (m_Anchor.m_Horizontal == HorizontalAlignment::eRight && m_Anchor.m_Vertical == VerticalAlignment::eTop)
            {
                currentChild->SetPosition(m_BaseRectangle.x - iStackWidth, m_BaseRectangle.y);
            }
            else if (m_Alignment == StackpanelAlignment::eVertical   && m_Anchor.m_Horizontal == HorizontalAlignment::eRight || 
                     m_Alignment == StackpanelAlignment::eHorizontal && m_Anchor.m_Horizontal == HorizontalAlignment::eRight)
            {
                currentChild->SetPosition(m_BaseRectangle.x - iStackWidth, m_BaseRectangle.y - iStackHeight);
            }
            else
            {
                currentChild->SetPosition(m_BaseRectangle.x, m_BaseRectangle.y - iStackHeight);
            }
        }
        else
        {
            UIBase* prevChild = m_Children[x - 1];
            int iCurrChildY = prevChild->GetPositionY() + prevChild->GetHeight() + m_iPadding;
            int iCurrChildX = prevChild->GetPositionX() + prevChild->GetWidth()  + m_iPadding;
            if (m_Alignment == StackpanelAlignment::eVertical && m_Anchor.m_Horizontal == HorizontalAlignment::eRight)
            {
                currentChild->SetPosition(m_BaseRectangle.x - iStackWidth, iCurrChildY);
            }
            else if (m_Alignment == StackpanelAlignment::eVertical)
            {
                currentChild->SetPosition(m_BaseRectangle.x, iCurrChildY);
            }
            else
            {
                currentChild->SetPosition(iCurrChildX, m_BaseRectangle.y - iStackHeight);
            }
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::AddChild(UIBase* child)
{
    m_Children.push_back(child);

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetChildAlignment(StackpanelAlignment alignment)
{
    m_Alignment = alignment;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetPadding(int padding)
{
    m_iPadding = padding;

    RefreshUI();
}

}