#include "PauseScreen.h"
#include "GameGlobals.h"
#include "Game/Managers/UIManager.h"
#include "Core/Systems/Systems.h"
#include "Core/Managers/SettingsManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
PauseScreen::PauseScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
PauseScreen::~PauseScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Update()
{
    m_ReturnToGameButton.Update();
    m_QuitGameButton.Update();

    // Button Click Event Check
    if (m_ReturnToGameButton.LeftClickPressed())
    {
        g_GameGlobals.m_bGamePaused = false;
        g_UIManager.ActivatePauseMenu();
    }

    if (m_QuitGameButton.LeftClickPressed())
    {
        g_GameGlobals.m_bGameRunning = false;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Draw(SDL_Renderer* renderer)
{
    m_BackgroundBox.Draw(renderer);
    m_Title.Draw(renderer);
    m_EngineText.Draw(renderer);
    m_Stack.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Initialize()
{
    m_BackgroundBox.SetAnchor(Anchor::eCenter);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
    m_BackgroundBox.SetSize(500, CoreManagers::g_SettingsManager.GetScreenHeight() - 50);
    m_BackgroundBox.SetOffset(
        (m_BackgroundBox.GetWidth() / 2) * -1, 
        (m_BackgroundBox.GetHeight() / 2) * -1
    );


    m_Title.SetAnchor(Anchor::eTopCenter);
    m_Title.SetText("Pause Menu");
    m_Title.SetOffset(
        ( (m_Title.GetWidth() / 2) * -1), 
        75
    );

    m_EngineText.SetAnchor(Anchor::eTopCenter);
    m_EngineText.SetText("MarkTwo Engine v2.0");
    m_EngineText.SetOffset(
        ( (m_EngineText.GetWidth() / 2) * -1),
        200
    );

    m_ReturnToGameButton.SetText("RETURN");
    m_ReturnToGameButton.SetSize(300,50);

    m_QuitGameButton.SetText("QUIT");
    m_QuitGameButton.SetSize(300,50);

    m_Stack.SetAnchor(Anchor::eCenter);
    m_Stack.SetPadding(25);
    m_Stack.AddChild(&m_ReturnToGameButton);
    m_Stack.AddChild(&m_QuitGameButton);
    m_Stack.SetOffset(
        ((m_Stack.GetWidth() / 2) * -1 ),
        150
    );

}

}