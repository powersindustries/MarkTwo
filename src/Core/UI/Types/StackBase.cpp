#include "StackBase.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
StackBase::StackBase()
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 0;
    m_BaseRectangle.h = 0;

    m_iPadding = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackBase::ClearChildren()
{
    m_Children.clear();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackBase::SetPadding(const int padding)
{
    m_iPadding = padding;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackBase::Update()
{
    UIBase::Update();

    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x=0; x < childCount; ++x)
    {
        UIBase* currPrimitive = m_Children[x];
        currPrimitive->Update();
    }
}

}