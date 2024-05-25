#ifndef StyleTypes_h
#define StyleTypes_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

namespace UI
{

struct TextBlockStyle
{
    uint32_t m_uiId;
    uint32_t m_uiFont;
    
    SDL_Color m_Color;
    std::string m_sDefaultText;
};

struct ButtonStyle
{
    uint32_t m_uiId;
    uint32_t m_uiFont;

    SDL_Color m_HoverColor;
    SDL_Color m_PressedColor;
    SDL_Color m_TextColor;
    SDL_Color m_BaseColor;

    std::string m_sDefaultText;
};

}

#endif