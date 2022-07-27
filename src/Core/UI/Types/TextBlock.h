#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../UICoreTypes.h"
#include "Core/Types/String.h"

namespace CoreUI
{
class TextBlock : public UIBase
{
public:
    TextBlock();
    ~TextBlock();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void SetPosition(int x, int y);
    void RefreshUI();


    void SetSize(int width, int height);
    void SetFont(CoreTypes::String fontID);
    void SetColor(SDL_Color color);
    void SetText(CoreTypes::String text);

    inline CoreTypes::String GetText() const { return m_Text; };


private:
    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    SDL_Color m_Color;

    CoreTypes::String m_Text;

};
}