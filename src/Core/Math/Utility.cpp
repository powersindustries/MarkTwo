#include "Utility.h"
#include <cmath>
#include <cfloat>

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
double Utility::DistanceBetweenTwoPoints(const int rect1X, const int rect1Y, const int rect2X, const int rect2Y)
{
    return sqrt(pow((rect1X - rect2X), 2) + pow((rect1Y - rect2Y), 2));
}


// -------------------------------------------------------
// -------------------------------------------------------
double Utility::DirectionalDistanceBetweenTwoRectangles(const MarkTwo::Direction& direction, const SDL_Rect& rect1, const SDL_Rect& rect2)
{
    switch (direction)
    {
    case MarkTwo::Direction::eUp:
    {
        return abs(rect1.y - (rect2.y + rect2.h));
    }
    case MarkTwo::Direction::eDown:
    {
        return abs((rect1.y + rect1.h) - rect2.y);
    }
    case MarkTwo::Direction::eLeft:
    {
        return abs(rect1.x - (rect2.x + rect2.w));
    }
    case MarkTwo::Direction::eRight:
    {
        return abs((rect1.x + rect1.w) - rect2.x);
    }
    }

    return DBL_MAX;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool Utility::CollisionBetweenTwoRectangles(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
    return  rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.h + rect1.y > rect2.y;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool Utility::CollisionBetweenTwoRectanglesWithPadding(const SDL_Rect& rect1, const SDL_Rect& rect2, const int padding)
{
    return (rect1.x - padding) < rect2.x + rect2.w &&
           (rect1.x + rect1.w + padding) > rect2.x &&
           (rect1.y - padding) < rect2.y + rect2.h &&
           (rect1.h + rect1.y + padding) > rect2.y;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool Utility::CollisionBetweenPointAndRectangle(const SDL_Rect& rect, const Core::Vec2i& v2i)
{
    return !((v2i.m_X < rect.x)
        || (v2i.m_X > rect.x + rect.w)
        || (v2i.m_Y < rect.y)
        || (v2i.m_Y > rect.y + rect.h));
}


// -------------------------------------------------------
// -------------------------------------------------------
double Utility::ATan2InDegrees(const int x, const int y)
{
    const double dRadians = atan2(y, x);
    return dRadians * (180.0 / MarkTwo::g_GameGlobals.PI);
}


// -------------------------------------------------------
// -------------------------------------------------------
double Utility::ATan2InRadians(const int x, const int y)
{
    return atan2(static_cast<double>(y), static_cast<double>(x));
}


// -------------------------------------------------------
// -------------------------------------------------------
bool Utility::StringToBool(const std::string& text)
{
    return (text == "True" || text == "true" || text == "T" || text == "t") ? true : false;
}
}