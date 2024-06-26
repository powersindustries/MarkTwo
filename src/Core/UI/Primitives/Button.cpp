#include "Button.h"
#include "GameGlobals.h"
#include "Core/Game.h"
#include "Core/Systems/Systems.h"
#include "Core/Managers/AssetManager.h"
#include "Core/UI/Types/StyleTypes.h"
#include "Core/UI/UIManager.h"

#define DEFAULT_PADDING 10

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
Button::Button()
        : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_TextRectangle.x = 0;
    m_TextRectangle.y = 0;
    m_TextRectangle.w = 100;
    m_TextRectangle.h = 100;

    m_BaseColor = MarkTwo::g_GameGlobals.COLOR_BLACK;
    m_HoverColor = MarkTwo::g_GameGlobals.COLOR_GRAY;
    m_PressedColor = MarkTwo::g_GameGlobals.COLOR_WHITE;
    m_TextColor = MarkTwo::g_GameGlobals.COLOR_WHITE;

    m_iData1 = 0;
    m_iData2 = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    if (MouseHovered())
    {
        if (LeftClickPressed() || RightClickPressed())
        {
            SDL_SetRenderDrawColor(renderer,
                                   m_PressedColor.r,
                                   m_PressedColor.g,
                                   m_PressedColor.b,
                                   m_PressedColor.a);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer,
                                   m_HoverColor.r,
                                   m_HoverColor.g,
                                   m_HoverColor.b,
                                   m_HoverColor.a);
        }
    }
    else
    {
        SDL_SetRenderDrawColor(renderer,
                               m_BaseColor.r,
                               m_BaseColor.g,
                               m_BaseColor.b,
                               m_Visibility == UIVisibility::eVisible ? m_BaseColor.a : (m_BaseColor.a / 2));
    }

    SDL_RenderFillRect(renderer, &m_BaseRectangle);
    SDL_RenderCopy(renderer, m_MessageTexture, NULL, &m_TextRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetStyle(uint32_t uiStyleId)
{
    const UI::ButtonStyle& currStyleData = g_UIManager.GetButtonStyle(uiStyleId);

    m_Font = Core::g_AssetManager.m_FontAssetsMap[currStyleData.m_uiFont].m_Font;

    m_BaseColor = currStyleData.m_BaseColor;
    m_HoverColor = currStyleData.m_HoverColor;
    m_PressedColor = currStyleData.m_PressedColor;
    m_TextColor = currStyleData.m_TextColor;

    if (m_Text.empty())
    {
        m_Text = currStyleData.m_sDefaultText;
    }

    m_bStyleSet = true;

    CreateWordTexture();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetText(const std::string& text)
{
    m_Text = text;

    CreateWordTexture();
    RefreshUI();

    if (m_TextRectangle.w > m_BaseRectangle.w)
    {
        SetSize(m_TextRectangle.w + DEFAULT_PADDING, m_BaseRectangle.h);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::RefreshUI()
{
    UIBase::RefreshUI();

    UpdateTextPositionInternal();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetOffset(const int x, const int y)
{
    UIBase::SetOffset(x, y);

    UpdateTextPositionInternal();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetPositionNoRefresh(const int x, const int y)
{
    UIBase::SetPositionNoRefresh(x, y);

    UpdateTextPositionInternal();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::CreateWordTexture()
{
    SDL_Color tempColor =
            {
                    m_TextColor.r,
                    m_TextColor.g,
                    m_TextColor.b,
                    m_Visibility == UIVisibility::eVisible ? static_cast<Uint8>(m_TextColor.a) : static_cast<Uint8>(
                            m_TextColor.a / 2)
            };

    SDL_Surface* surface = nullptr;
    if (m_Font)
    {
        surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), tempColor);
    }
    else
    {
        surface = TTF_RenderText_Solid(g_UIManager.GetDefaultFont(), m_Text.c_str(), tempColor);
    }

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(MarkTwo::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);

    SDL_Point textureSize;
    SDL_QueryTexture(m_MessageTexture, NULL, NULL, &textureSize.x, &textureSize.y);
    m_TextRectangle.w = textureSize.x;
    m_TextRectangle.h = textureSize.y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::UpdateTextPositionInternal()
{
    m_TextRectangle.x = m_BaseRectangle.x + (m_BaseRectangle.w / 2) - (m_TextRectangle.w / 2);
    m_TextRectangle.y = m_BaseRectangle.y + (m_BaseRectangle.h / 2) - (m_TextRectangle.h / 2);
}

}