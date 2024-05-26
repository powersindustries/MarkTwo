#include "Box.h"
#include "GameGlobals.h"
#include "Core/Systems/Logging.h"
#include "Core/Managers/EventManager.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
int Box::m_iUniqueId = 0;


// -------------------------------------------------------
// -------------------------------------------------------
void Box::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    // Draw Background.
    SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b,
                           m_Visibility == UIVisibility::eVisible ? m_Color.a : (m_Color.a / 2));
    SDL_RenderFillRect(renderer, &m_BaseRectangle);

    // Draw children.
    StackBase::Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::RefreshUI()
{
    // Empty Box. Go off size.
    if (m_Children.size() == 0)
    {
        UIBase::RefreshUI();
    }
    // Box has children. Go off childen + margin.
    else
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

        m_BaseRectangle.w = maxWidth + m_Margin.m_iLeft + m_Margin.m_iRight;
        m_BaseRectangle.h = height + (m_iPadding * childCount) + m_Margin.m_iTop + m_Margin.m_iBottom;

        // Refresh VerticalStack's UI first.
        UIBase::RefreshUI();

        // Set the offset position of each child.
        // Set the VerticalStack's width and height as well.
        int heightOffset = 0;
        for (int x = 0; x < childCount; ++x)
        {
            UIBase* currChild = m_Children[x];

            currChild->SetPositionNoRefresh(m_BaseRectangle.x + m_Margin.m_iLeft, (m_BaseRectangle.y + heightOffset) + m_Margin.m_iTop);
            heightOffset = currChild->GetHeight() + m_iPadding;
        }
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::AddChild(UIBase* child)
{
    // Give Child parent ID.
    std::string eventId = "event_box_";
    eventId.append(!m_sId.empty() ? m_sId : std::to_string(m_iUniqueId));
    child->m_sParentId = eventId;
    Core::g_EventManager.Subscribe(child->m_sParentId, [this](){ Box::RefreshUI(); });

    m_Children.push_back(child);

    m_iUniqueId++;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetMargin(const Margin& margin)
{
    m_Margin = margin;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetPositionNoRefresh(const int x, const int y)
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