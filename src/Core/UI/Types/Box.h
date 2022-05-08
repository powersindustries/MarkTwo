#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "../UICoreTypes.h"

namespace CoreUI
{
class Box : public UIBase
{
public:
    Box();
    ~Box();

    // UIBase Methods and Data
    void Update();
    void Update(bool leftClicked, bool rightClicked);
    void Draw(SDL_Renderer* renderer);

    void SetAnchor(HorizontalAlignment horizontal, VerticalAlignment vertical);
    void SetElementAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical);
    void SetOffset(int xOffset, int yOffset);
    void SetPosition(int x, int y);

    int GetWidth() { return m_BaseRectangle.w; }
    int GetHeight() { return m_BaseRectangle.h; }

    void RefreshUI();

    AlignmentData m_Anchor;
    AlignmentData m_ElementAlignment;
    CoreMath::Vector2i m_Offset;


public:

    void SetSize(int width, int height);
    void SetColor(SDL_Color color) { m_Color = color; }


private:
    SDL_Rect m_BaseRectangle;
    SDL_Color m_Color;

};
}