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
    m_Title.SetAnchor(Anchor::eTopCenter);
    m_Title.SetText("MarkTwo Engine v2.0");
    m_Title.SetOffset( 
        ( (m_Title.GetWidth() / 2) * -1 ), 
        50
    );

    m_TitleBox.SetAnchor(Anchor::eTopCenter);
    m_TitleBox.SetColor(g_GameGlobals.COLOR_WHITE);
    m_TitleBox.SetSize( 
        (m_Title.GetWidth() + 50),
        (m_Title.GetHeight() + 50)
    );
    m_TitleBox.SetOffset(
        ( (m_TitleBox.GetWidth() / 2) * -1 ), 
        25
    );
    
    m_PlayerText.SetAnchor(Anchor::eTopLeft);
    m_PlayerText.SetText("Player Below");
    m_PlayerText.SetOffset(50,50);

    m_PlayerBox.SetAnchor(Anchor::eTopLeft);
    m_PlayerBox.SetColor(g_GameGlobals.COLOR_WHITE);
    m_PlayerBox.SetSize(
        (m_PlayerText.GetWidth() + 50),
        (m_PlayerText.GetHeight() + 50)
    );
    m_PlayerBox.SetOffset(25,25);

    m_DirectionTitle.SetText("Directions:");
    m_MovementText.SetText("WASD - Movement");
    m_PauseText.SetText("ESC - Pause Menu");
    m_DebugText.SetText("F1 - Debug Mode");
    m_KillGameText.SetText("Backspace - End");

    m_DirectionsStack.SetAnchor(Anchor::eTopRight);
    m_DirectionsStack.SetOffset(-50,50);
    m_DirectionsStack.SetPadding(20);
    m_DirectionsStack.AddChild(&m_DirectionTitle);
    m_DirectionsStack.AddChild(&m_MovementText);
    m_DirectionsStack.AddChild(&m_PauseText);
    m_DirectionsStack.AddChild(&m_DebugText);
    m_DirectionsStack.AddChild(&m_KillGameText);

    m_DirectionsBox.SetAnchor(Anchor::eTopRight);
    m_DirectionsBox.SetColor(g_GameGlobals.COLOR_WHITE);
    m_DirectionsBox.SetOffset(-25,25);
    m_DirectionsBox.SetSize(
        (m_DirectionsStack.GetWidth() + 50),
        (m_DirectionsStack.GetHeight() + 50)
    );

    m_EventInfoText.SetAnchor(Anchor::eBottomCenter);
    m_EventInfoText.SetText("Press F4 to trigger TestEvent and event system");
    m_EventInfoText.SetOffset(
        ( (m_EventInfoText.GetWidth() / 2) * -1 ),
        -25
    );

}

}