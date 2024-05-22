#ifndef Button_h
#define Button_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "Core/UI/Types/UIBase.h"
#include "Core/Managers/InputManager.h"

namespace UI
{
class Button : public UIBase
{
public:

    Button();

    void Draw(SDL_Renderer* renderer) override;
    void SetStyle(uint32_t uiStyleId) override;

    void RefreshUI() override;

    void SetOffset(const int x, const int y) override;
    void SetText(const std::string& text);

    inline void SetBackgroundColor(const SDL_Color& color) { m_BaseColor = color; };
    inline void SetHoverColor(const SDL_Color& color) { m_HoverColor = color; };
    inline uint32_t GetData1() const { return m_iData1; };
    inline uint32_t GetData2() const { return m_iData2; };
    inline void SetData1(const uint32_t data) { m_iData1 = data; };
    inline void SetData2(const uint32_t data) { m_iData2 = data; };


private:

    void CreateWordTexture();
    void UpdateTextPositionInternal();


protected:

    void SetPositionNoRefresh(const int x, const int y) override;


private:

    TTF_Font* m_Font;
    SDL_Texture* m_MessageTexture;
    SDL_Rect m_TextRectangle {};

    std::string m_Text;

    SDL_Color m_BaseColor {};
    SDL_Color m_HoverColor {};
    SDL_Color m_PressedColor {};
    SDL_Color m_TextColor {};

    int32_t m_iData1;
    int32_t m_iData2;

};
}

#endif