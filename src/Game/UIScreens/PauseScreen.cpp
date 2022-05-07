#include "PauseScreen.h"
#include "Core/Managers/InputManager.h"
#include "GameGlobals.h"
#include "Core/Managers/UIManager.h"
#include "Core/Managers/LoadManager.h"

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
    m_ReturnToGameButton.Update(g_InputManager.m_MouseButtonData.m_LeftClicked, g_InputManager.m_MouseButtonData.m_RightClicked);
    m_QuitGameButton.Update(g_InputManager.m_MouseButtonData.m_LeftClicked, g_InputManager.m_MouseButtonData.m_RightClicked);

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
    m_BackgroundBox.SetWidth(500);
    m_BackgroundBox.SetHeight(g_GameGlobals.WINDOW_HEIGHT - 50);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);

    m_Title.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_Title.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_Title.SetOffset(0, 75);
    m_Title.SetFont("fnt_Charriot");
    m_Title.SetText("Pause Menu");
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);

    m_EngineText.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_EngineText.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_EngineText.SetOffset(0, 200);
    m_EngineText.SetFont("fnt_Charriot");
    m_EngineText.SetText("MarkTwo Engine v2.0");
    m_EngineText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_ReturnToGameButton.SetFont("fnt_Arial");
    m_ReturnToGameButton.SetText("RETURN TO GAME");
    m_ReturnToGameButton.SetWidth(300);
    m_ReturnToGameButton.SetHeight(50);

    m_QuitGameButton.SetFont("fnt_Arial");
    m_QuitGameButton.SetText("QUIT GAME");
    m_QuitGameButton.SetWidth(300);
    m_QuitGameButton.SetHeight(50);

    m_StackPanel.SetAnchor(HorizontalAlignment::eCenter,VerticalAlignment::eBottom);
    m_StackPanel.SetElementAlignment(HorizontalAlignment::eCenter,VerticalAlignment::eCenter);
    m_StackPanel.SetOffset(0,150);
    m_StackPanel.AddChild(&m_ReturnToGameButton);
    m_StackPanel.AddChild(&m_QuitGameButton);
    m_StackPanel.SetPadding(25);

}

}