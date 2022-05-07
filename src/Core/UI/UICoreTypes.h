#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "../Math/Vector.h"

namespace CoreUI
{


enum class HorizontalAlignment
{
    eLeft,
    eCenter,
    eRight
};


enum class VerticalAlignment
{
    eTop,
    eCenter,
    eBottom
};


class AlignmentData
{
public:
    HorizontalAlignment m_Horizontal;
    VerticalAlignment   m_Vertical;

    // Default all anchors to be top left corner
    AlignmentData()
    {
        m_Horizontal  = HorizontalAlignment::eLeft;
        m_Vertical    = VerticalAlignment::eTop;
    }

    AlignmentData(HorizontalAlignment horizontal, VerticalAlignment vertical)
    {
        m_Horizontal = horizontal;
        m_Vertical   = vertical;
    }

    ~AlignmentData() {}
};


class UIBase
{
public:
    virtual void Update() = 0;
    virtual void Update(bool leftClicked, bool rightClicked) = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;

    virtual void SetAnchor(HorizontalAlignment horizontal, VerticalAlignment vertical) = 0;
    virtual void SetElementAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical) = 0;
    virtual void SetOffset(int xOffset, int yOffset) = 0;
    virtual void SetPosition(int x, int y) = 0;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;

    virtual void RefreshUI() = 0;

    // Anchor point (x,y) relative to entire screen.
    AlignmentData m_Anchor;
    // How the UI elements are aligned around it's position.
    AlignmentData m_ElementAlignment;
    // Offset position based on the anchor point.
    CoreMath::Vector2i m_Offset;

};


class UIScreenBase
{
    virtual void Update() = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void Initialize() = 0;
};

}