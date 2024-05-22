#ifndef TextBlock_h
#define TextBlock_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include "Core/UI/Types/UIBase.h"


namespace UI
{
class TextBlock : public UIBase
{
public:

    TextBlock();

    void Draw(SDL_Renderer* renderer) override;

    void SetStyle(const uint32_t styleId) override;
    void SetFont(const uint32_t fontIdHash);
    void SetColor(const SDL_Color& color) override;
    void SetText(const std::string& text);
    void SetWordWrap(const uint8_t uiWordWrap);
    void SetVisibility(const UIVisibility& visibility) override;
    void SetSize(const int x, const int y) override;

    inline const std::string GetText() { return m_Text; };


private:

    void CreateWordTexture();


private:

    std::string m_Text;

    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    Core::Vec2i m_vSize;

    uint8_t m_uiWordWrap;

};
}

#endif