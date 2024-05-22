#include "Transform.h"
#include <iostream>

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
Transform::Transform()
{
    m_iPositionX = 0;
    m_iPositionY = 0;
    m_iWidth     = 0;
    m_iHeight    = 0;
    m_iScale     = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetTransform(const SDL_Rect& rectangle, int s /*= 1*/)
{
    m_iPositionX = rectangle.x;
    m_iPositionY = rectangle.y;
    m_iWidth     = rectangle.w;
    m_iHeight    = rectangle.h;
    m_iScale     = s;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetTransform(const int x, const int y, const int w, const int h, int s /*= 1*/)
{
    m_iPositionX = x;
    m_iPositionY = y;
    m_iWidth     = w;
    m_iHeight    = h;
    m_iScale     = s;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetPosition(const int x, const int y)
{
    m_iPositionX = x;
    m_iPositionY = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetPosition(const SDL_Rect& rectangle)
{
    m_iPositionX = rectangle.x;
    m_iPositionY = rectangle.y;
}


}