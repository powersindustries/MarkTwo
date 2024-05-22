#ifndef UICoreTypes_h
#define UICoreTypes_h

#include <cstdint>

namespace UI
{

enum class Anchor
{
    eTopLeft,
    eTopCenter,
    eTopRight,
    eCenterLeft,
    eCenter,
    eCenterRight,
    eBottomLeft,
    eBottomCenter,
    eBottomRight
};

enum class UIVisibility
{
    eVisible,
    eHidden,
    eDisabled
};

enum MouseState
{
    eHover  = 1 << 0, // Mouse Hover
    eLMouse = 1 << 1, // Left Mouse
    eRMouse = 1 << 2  // Right Mouse
};

struct Margin
{
    int m_iLeft = 0;
    int m_iRight = 0;
    int m_iTop = 0;
    int m_iBottom = 0;
};

}

#endif