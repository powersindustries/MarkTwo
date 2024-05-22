#include "Box.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
Box::Box()
        : m_Stack(nullptr)
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b,
                           m_Visibility == UIVisibility::eVisible ? m_Color.a : (m_Color.a / 2));
    SDL_RenderFillRect(renderer, &m_BaseRectangle);

    if (m_Stack)
    {
        m_Stack->Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::RefreshUI()
{
    if (m_Stack)
    {
        m_BaseRectangle.w = m_Stack->GetWidth() + m_Margin.m_iLeft + m_Margin.m_iRight;
        m_BaseRectangle.h = m_Stack->GetHeight() + m_Margin.m_iTop + m_Margin.m_iBottom;
    }

    UIBase::RefreshUI();

    if (m_Stack)
    {
        m_Stack->SetPositionNoRefresh(m_BaseRectangle.x + m_Margin.m_iLeft, m_BaseRectangle.y + m_Margin.m_iTop);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::AddChild(UIBase* child)
{
    if (!m_Stack)
    {
        // If child is a stack, set m_stack to incoming stack. Using VerticalStack as default.
        VerticalStack* childAsStack = dynamic_cast<VerticalStack*>(child);
        if (childAsStack)
        {
            m_Stack = childAsStack;
        }
        else
        {
            m_Stack = new VerticalStack();
            m_Stack->AddChild(child);
        }

        RefreshUI();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetVisibility(const UIVisibility& visibility)
{
    UIBase::SetVisibility(visibility);

    m_Stack->SetVisibility(visibility);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetMargin(const Margin& margin)
{
    m_Margin = margin;

    RefreshUI();
}

}