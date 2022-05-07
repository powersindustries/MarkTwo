#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "../UICoreTypes.h"
#include <string>

namespace CoreUI
{
class Button : public UIBase
{
public:
    Button();
    ~Button();

    // UIBase Methods and Data
    void Update() {}
    void Update(bool leftClicked, bool rightClicked);
    void Draw(SDL_Renderer* renderer);

    void SetAnchor(HorizontalAlignment horizontal, VerticalAlignment vertical);
    void SetElementAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical);
    void SetOffset(int xOffset, int yOffset);
    void SetPosition(int x, int y);

    int GetWidth() { return m_BaseRectangle.w; };
    int GetHeight() { return m_BaseRectangle.h; }

    void RefreshUI();

    AlignmentData m_Anchor;
    AlignmentData m_ElementAlignment;
    CoreMath::Vector2i m_Offset;


public:

    bool LeftClickPressed() { return m_LeftClickPressed; }
    bool RightClickPressed() { return m_RightClickPressed; }

    void SetFont(std::string fontID);

    int GetPositionX() { return m_BaseRectangle.x; }
    int GetPositionY() { return m_BaseRectangle.y; }

    void SetWidth(int width);
    void SetHeight(int height);
    void SetText(std::string text);
    void SetTextAlignment(HorizontalAlignment alignment);


private:
    bool MouseCollisionDetected(int mouseX, int mouseY);
    void RefreshInternalUI();


private:

    // SDL Types
    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    SDL_Rect m_FontRectangle;
    SDL_Rect m_BaseRectangle;

    // Button States
    bool m_LeftClickPressed;
    bool m_RightClickPressed;

    // Button Text
    std::string m_Text;
    HorizontalAlignment m_TextAlignment = HorizontalAlignment::eCenter;

};
}