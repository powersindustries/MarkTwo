#include "VerticalStack.h"
#include "Core/Systems/Logging.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::RefreshUI()
{
    // Get the width of the largest child and the max height of all children.
    int maxWidth = m_BaseRectangle.w;
    int height = 0;
    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < childCount; ++x)
    {
        const int currWidth = m_Children[x]->GetWidth();
        const int currHeight = m_Children[x]->GetHeight();

        maxWidth = maxWidth > currWidth ? maxWidth : currWidth;
        height += currHeight;
    }

    m_BaseRectangle.w = maxWidth;
    m_BaseRectangle.h = height + (m_iPadding * childCount);

    // Refresh VerticalStack's UI first.
    UIBase::RefreshUI();

    // Set the offset position of each child.
    // Set the VerticalStack's width and height as well.
    int heightOffset = 0;
    for (int x = 0; x < childCount; ++x)
    {
        UIBase* currChild = m_Children[x];

        currChild->SetPositionNoRefresh(m_BaseRectangle.x, (m_BaseRectangle.y + heightOffset));
        heightOffset = currChild->GetHeight() + m_iPadding;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::AddChild(UIBase* child)
{
    m_Children.push_back(child);

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::SetVisibility(const UIVisibility& visibility)
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
void VerticalStack::SetPositionNoRefresh(const int x, const int y)
{
    UIBase::SetPositionNoRefresh(x, y);

    // Reset base rectangle's Width and Height.
    m_BaseRectangle.w = 0;
    m_BaseRectangle.h = 0;

    // Set original anchor points of children.
    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t i = 0; i < childCount; ++i)
    {
        m_Children[i]->SetAnchor(m_Anchor);
    }

    // Set the offset position of each child.
    // Set the VerticalStack's width and height as well.
    for (uint8_t i = 0; i < childCount; ++i)
    {
        UIBase* currChild = m_Children[i];
        if (currChild)
        {
            // Set the position of current child.
            currChild->SetPositionNoRefresh(m_BaseRectangle.x, (m_BaseRectangle.y + m_BaseRectangle.h));

            // Update the width and height of stack.
            const int currChildWidth = currChild->GetWidth();
            if (currChildWidth > m_BaseRectangle.w)
            {
                m_BaseRectangle.w = currChildWidth;
            }

            m_BaseRectangle.h += currChild->GetHeight() + m_iPadding;
        }
        else
        {
            Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "currChild in VerticalStack is nullptr.");
        }
    }
}

}