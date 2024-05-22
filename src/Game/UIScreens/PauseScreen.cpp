#include "PauseScreen.h"
#include "GameGlobals.h"
#include "Game/Managers/FrontendManager.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/UI/UIManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
PauseScreen::PauseScreen()
{
    m_sScreenID = "pause_screen";
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Initialize()
{
    UIScreenBase::Initialize();

    m_Widget = UI::g_UIManager.GetWidgetByID(m_sWidgetId);

    m_ReturnButton = dynamic_cast<Button*>(UI::g_UIManager.GetPrimitiveByID("return_button"));
    m_QuitButton = dynamic_cast<Button*>(UI::g_UIManager.GetPrimitiveByID("quit_button"));

    assert(m_ReturnButton && m_QuitButton);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Update()
{
    m_Widget->Update();

    // Button Click Event Check
    if (m_ReturnButton && m_ReturnButton->LeftClickPressed())
    {
        g_GameGlobals.m_bGamePaused = false;
        RemoveSelf();
    }

    if (m_QuitButton && m_QuitButton->LeftClickPressed())
    {
        g_GameGlobals.m_bGameRunning = false;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Draw(SDL_Renderer* renderer)
{
    m_Widget->Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::RemoveSelf()
{
    g_FrontendManager.RemoveScreen(m_sScreenID);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::HotReloadUI()
{
    m_Widget = UI::g_UIManager.GetWidgetByID(m_sWidgetId);
}

}