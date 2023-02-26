#include "PauseScreen.h"
#include "GameGlobals.h"
#include "Game/Managers/UIManager.h"
#include "Game/Managers/LoadManager.h"
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
    m_ReturnToGameButton.Update(CoreManagers::g_InputManager);
    m_QuitGameButton.Update(CoreManagers::g_InputManager);

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
    m_StackPanel.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Initialize()
{
    m_BackgroundBox.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetSize(500, CoreManagers::g_SettingsManager.GetScreenHeight() - 50);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);

    m_Title.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_Title.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_Title.SetOffset(0, 75);
    m_Title.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_Title.SetText("Pause Menu");
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);

    m_EngineText.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_EngineText.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_EngineText.SetOffset(0, 200);
    m_EngineText.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Charriot")));
    m_EngineText.SetText("MarkTwo Engine v2.0");
    m_EngineText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_ReturnToGameButton.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Arial")));
    m_ReturnToGameButton.SetText("RETURN TO GAME");
    m_ReturnToGameButton.SetSize(300,50);

    m_QuitGameButton.SetFont(CoreSystems::StringToHash32(CoreTypes::String("fnt_Arial")));
    m_QuitGameButton.SetText("QUIT GAME");
    m_QuitGameButton.SetSize(300,50);

    m_StackPanel.SetAnchor(HorizontalAlignment::eCenter,VerticalAlignment::eBottom);
    m_StackPanel.SetElementAlignment(HorizontalAlignment::eCenter,VerticalAlignment::eTop);
    m_StackPanel.SetPadding(25);
    m_StackPanel.SetOffset(0,150);
    m_StackPanel.AddChild(&m_ReturnToGameButton);
    m_StackPanel.AddChild(&m_QuitGameButton);

}

}