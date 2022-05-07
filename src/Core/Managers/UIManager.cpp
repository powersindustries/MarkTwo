#include "UIManager.h"
#include <Windows.h>
#include "GameGlobals.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
UIManager g_UIManager;


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::UIManager()
{
    m_ActiveScreen = ActiveScreen::eHud;
}


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::~UIManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::InitializeUIScreens()
{
    m_HUDScreen.Initialize();
    m_PauseScreen.Initialize();
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Update()
{
    switch (m_ActiveScreen)
    {
    case ActiveScreen::eHud:
        m_HUDScreen.Update();
        break;
    case ActiveScreen::ePause:
        m_PauseScreen.Update();
        break;
    default:
        OutputDebugString("MESSAGE: UI Update corrupted.");
        break;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Draw(SDL_Renderer* renderer)
{
    switch (m_ActiveScreen)
    {
    case ActiveScreen::eHud:
        m_HUDScreen.Draw(renderer);
        break;
    case ActiveScreen::ePause:
        m_PauseScreen.Draw(renderer);
        break;
    default:
        OutputDebugString("MESSAGE: UI Draw corrupted.");
        break;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::ActivatePauseMenu()
{
    if (m_ActiveScreen == ActiveScreen::ePause)
    {
        m_ActiveScreen = ActiveScreen::eHud;
        g_GameGlobals.m_bGamePaused = false;
        return;
    }

    m_ActiveScreen = ActiveScreen::ePause;
}

}