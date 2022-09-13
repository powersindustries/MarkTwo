#include "HUDScreen.h"
#include "GameGlobals.h"
#include "Core/Systems/Systems.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
HUDScreen::HUDScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
HUDScreen::~HUDScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Draw(SDL_Renderer* renderer)
{
    m_TitleBox.Draw(renderer);
    m_Title.Draw(renderer);

    m_PlayerBox.Draw(renderer);
    m_PlayerText.Draw(renderer);

    m_DirectionsBox.Draw(renderer);
    m_DirectionsStack.Draw(renderer);

    m_EventInfoText.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Initialize()
{
    m_TitleBox.SetAnchor(HorizontalAlignment::eCenter,VerticalAlignment::eTop);
    m_TitleBox.SetElementAlignment(HorizontalAlignment::eCenter,VerticalAlignment::eCenter);
    m_TitleBox.SetOffset(0,50);
    m_TitleBox.SetSize(300,50);
    m_TitleBox.SetColor(g_GameGlobals.COLOR_WHITE);

    m_Title.SetAnchor(HorizontalAlignment::eCenter,VerticalAlignment::eTop);
    m_Title.SetElementAlignment(HorizontalAlignment::eCenter,VerticalAlignment::eCenter);
    m_Title.SetOffset(0,50);
    m_Title.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_Title.SetText("MarkTwo Engine v2.0");
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);

    
    m_PlayerBox.SetAnchor(HorizontalAlignment::eLeft,VerticalAlignment::eTop);
    m_PlayerBox.SetElementAlignment(HorizontalAlignment::eLeft,VerticalAlignment::eCenter);
    m_PlayerBox.SetOffset(50,50);
    m_PlayerBox.SetSize(250,50);
    m_PlayerBox.SetColor(g_GameGlobals.COLOR_WHITE);

    m_PlayerText.SetAnchor(HorizontalAlignment::eLeft,VerticalAlignment::eTop);
    m_PlayerText.SetElementAlignment(HorizontalAlignment::eLeft,VerticalAlignment::eCenter);
    m_PlayerText.SetOffset(100,50);
    m_PlayerText.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_PlayerText.SetText("Player Below");
    m_PlayerText.SetColor(g_GameGlobals.COLOR_BLACK);

    
    m_DirectionsBox.SetAnchor(HorizontalAlignment::eRight,VerticalAlignment::eTop);
    m_DirectionsBox.SetElementAlignment(HorizontalAlignment::eLeft,VerticalAlignment::eTop);
    m_DirectionsBox.SetOffset(50,25);
    m_DirectionsBox.SetSize(300,250);
    m_DirectionsBox.SetColor(g_GameGlobals.COLOR_WHITE);

    m_DirectionTitle.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_DirectionTitle.SetText("Directions:");
    m_DirectionTitle.SetColor(g_GameGlobals.COLOR_BLACK);

    m_MovementText.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_MovementText.SetText("WASD - Movement");
    m_MovementText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_PauseText.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_PauseText.SetText("ESC - Pause Menu");
    m_PauseText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_DebugText.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_DebugText.SetText("F1 - Debug Mode");
    m_DebugText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_KillGameText.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_KillGameText.SetText("Backspace - Kill Game");
    m_KillGameText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_DirectionsStack.SetAnchor(HorizontalAlignment::eRight, VerticalAlignment::eTop);
    m_DirectionsStack.SetChildAlignment(StackpanelAlignment::eVertical);
    m_DirectionsStack.SetOffset(65,50);
    m_DirectionsStack.SetPadding(20);
    m_DirectionsStack.AddChild(&m_DirectionTitle);
    m_DirectionsStack.AddChild(&m_MovementText);
    m_DirectionsStack.AddChild(&m_PauseText);
    m_DirectionsStack.AddChild(&m_DebugText);
    m_DirectionsStack.AddChild(&m_KillGameText);


    m_EventInfoText.SetAnchor(HorizontalAlignment::eRight,VerticalAlignment::eBottom);
    m_EventInfoText.SetElementAlignment(HorizontalAlignment::eCenter,VerticalAlignment::eTop);
    m_EventInfoText.SetOffset(0,10);
    m_EventInfoText.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_EventInfoText.SetText("Press F4 to trigger TestEvent and event system");
    m_EventInfoText.SetColor(g_GameGlobals.COLOR_BLACK);


}

}