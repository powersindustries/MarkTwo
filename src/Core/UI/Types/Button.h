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

    void Update();
    void Update(bool leftClicked, bool rightClicked);
    void Draw(SDL_Renderer* renderer);
    void SetPosition(int x, int y);
    void RefreshUI();

    void SetFont(std::string fontID);

    void SetSize(int width, int height);
    void SetText(std::string text);
    void SetTextAlignment(HorizontalAlignment alignment);

    inline bool LeftClickPressed() const { return m_LeftClickPressed; }
    inline bool RightClickPressed() const { return m_RightClickPressed; }



private:
    bool MouseCollisionDetected(int mouseX, int mouseY);
    void RefreshInternalUI();


private:

    // SDL Types
    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    SDL_Rect m_FontRectangle;

    // Button States
    bool m_LeftClickPressed;
    bool m_RightClickPressed;

    // Button Text
    std::string m_Text;
    HorizontalAlignment m_TextAlignment = HorizontalAlignment::eCenter;

};
}