#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>
#include "../UICoreTypes.h"
#include "Core/Math/Vector.h"

namespace CoreUI
{


enum class StackpanelAlignment
{
    eHorizontal,
    eVertical
};


class StackPanel : public UIBase
{
public:
    StackPanel();
    ~StackPanel();


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

    // Class Specific Methods
    void AddChild(UIBase* child);
    void SetChildAlignment(StackpanelAlignment alignment);
    void SetPadding(int padding);
    void ResizeSpacing();


public:
    std::vector<UIBase*> m_Children;


private:
    SDL_Rect m_BaseRectangle;

    int m_iPadding;

    StackpanelAlignment m_Alignment;

};
}