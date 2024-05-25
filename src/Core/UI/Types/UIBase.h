#ifndef UIBASE_H
#define UIBASE_H

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "Core/Math/VectorMethods.h"
#include "UICoreTypes.h"

namespace UI
{

// UIBase is the base class for all UI Primitives (EX: Buttons, TextBlocks, etc.).
class UIBase
{
public:

    UIBase();

    virtual void Draw(SDL_Renderer* renderer) = 0;

    virtual void Update();
    virtual void RefreshUI();

    void SetAnchor(const Anchor& anchor);
    void SetAlignment(const Anchor& alignment);
    virtual void SetOffset(const int x, const int y);
    virtual void SetVisibility(const UIVisibility& displayType) { m_Visibility = displayType; }
    virtual void SetSize(const int w, const int h);
    virtual void SetColor(const SDL_Color& color) { m_Color = color; }
    virtual void SetStyle(const uint32_t styleId) {};

    inline UIVisibility GetVisibility() const { return m_Visibility; }
    inline bool IsVisible() const { return m_Visibility != UIVisibility::eHidden; }
    inline bool IsDisabled() const { return m_Visibility == UIVisibility::eDisabled; }
    inline int GetWidth() const { return m_BaseRectangle.w; }
    inline int GetHeight() const { return m_BaseRectangle.h; }

    inline bool MouseHovered() const { return m_uiMouseState & MouseState::eHover; };
    inline bool LeftClickPressed() const { return m_uiMouseState & MouseState::eLMouse; };
    inline bool RightClickPressed() const { return m_uiMouseState & MouseState::eRMouse; };


protected:

    virtual void SetPositionNoRefresh(const int x, const int y);


public:

    // ID used to reference the primitive.
    std::string m_sId;

    // Dictates which part of the screen the UI is attached to.
    // Defaults value: X=0, Y=0, W=100, H=100
    SDL_Rect m_BaseRectangle {};


    // Dictates which part of the screen the UI is attached to.
    // Defaults value: Anchor::eTopLeft
    Core::Vec2i m_vOffset;


    // Dictates which part of the screen the UI is attached to.
    // Defaults value: Anchor::eTopLeft
    Anchor m_Anchor;


    // How should the UI element hang off of the anchor point.
    // Defaults value: Anchor::eTopLeft
    Anchor m_Alignment;


    // Dictates how a UI primitive should be drawn.
    // Defaults value: UIVisibility::eVisible
    UIVisibility m_Visibility;


    // State of the mouse interacting with the UI element.
    // Defaults value: 0
    uint8_t m_uiMouseState;


    // State of the mouse interacting with the UI element.
    // Defaults value: 0
    SDL_Color m_Color {};


protected:

    bool m_bStyleSet;

    friend class VerticalStack;
    friend class HorizontalStack;

};

}


#endif
