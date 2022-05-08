#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "../UICoreTypes.h"
#include <string>

namespace CoreUI
{
class TextBlock : public UIBase
{
public:
    TextBlock();
    ~TextBlock();


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

    int GetPositionX() { return m_BaseRectangle.x; }
    int GetPositionY() { return m_BaseRectangle.y; }

    void SetSize(int width, int height);
    void SetFont(std::string fontID);
    void SetColor(SDL_Color color);
    void SetText(std::string text);
    std::string GetText() { return m_Text; };


private:
    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    SDL_Rect m_BaseRectangle;
    SDL_Color m_Color;

    std::string m_Text;

};
}