#include "HorizontalStack.h"
#include "Core/Managers/SettingsManager.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
void HorizontalStack::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    const uint8_t uiChildCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < uiChildCount; ++x)
    {
        m_Children[x]->Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void HorizontalStack::RefreshUI()
{
    // Get the width and height of the children.
    int maxWidth = 0;
    int maxHeight = m_BaseRectangle.h;
    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < childCount; ++x)
    {
        const int currWidth = m_Children[x]->GetWidth();
        const int currHeight = m_Children[x]->GetHeight();

        maxWidth += currWidth;
        maxHeight = maxHeight > currHeight ? maxHeight : currHeight;
    }

    m_BaseRectangle.w = maxWidth + (m_iPadding * childCount);
    m_BaseRectangle.h = maxHeight;

    // Refresh HorizontalStack's UI first.
    UIBase::RefreshUI();

    // Set the offset position of each child.
    // Set the HorizontalStack's width and height as well.
    int widthOffset = 0;
    for (uint8_t x = 0; x < childCount; ++x)
    {
        UIBase* currChild = m_Children[x];
        currChild->SetPositionNoRefresh((m_BaseRectangle.x + widthOffset), m_BaseRectangle.y);
        widthOffset += currChild->GetWidth() + m_iPadding;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void HorizontalStack::AddChild(UIBase* child)
{
    m_Children.push_back(child);

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HorizontalStack::SetVisibility(const UIVisibility& visibility)
{
    UIBase::SetVisibility(visibility);

    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < childCount; ++x)
    {
        m_Children[x]->SetVisibility(m_Visibility);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void HorizontalStack::SetPositionNoRefresh(const int x, const int y)
{
    UIBase::SetPositionNoRefresh(x, y);

    // Reset base rectangle's Width and Height.
    m_BaseRectangle.w = 0;
    m_BaseRectangle.h = 0;

    // Set anchor points of children.
    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t i = 0; i < childCount; ++i)
    {
        m_Children[i]->SetAnchor(m_Anchor);
    }

    // Set the offset position of each child.
    // Set the HorizontalStack's width and height as well.
    for (int i = 0; i < childCount; ++i)
    {
        UIBase* currChild = m_Children[i];

        // Set the position of current child.
        currChild->SetPositionNoRefresh((m_BaseRectangle.x + m_BaseRectangle.w), m_BaseRectangle.y);

        const int iCurrChildHeight = currChild->GetHeight();
        if (iCurrChildHeight > m_BaseRectangle.h)
        {
            m_BaseRectangle.h = iCurrChildHeight;
        }

        m_BaseRectangle.w += currChild->GetWidth() + m_iPadding;
    }
}

}