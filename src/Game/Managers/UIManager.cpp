#include "UIManager.h"

#include "Core/Systems/Systems.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
UIManager g_UIManager;


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::UIManager()
{
    // Default add HUD UI Screen to stack.
    m_ScreenStack.push(UI::UIScreenID::eHud);
}


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::~UIManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Initialize()
{
    m_HUDScreen.Initialize();
    m_PauseScreen.Initialize();
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Update()
{
    switch (GetActiveScreenID())
    {
    case UIScreenID::eHud : 
    {
        m_HUDScreen.Update();
        break;
    }
    case UIScreenID::ePause :
    {
        m_PauseScreen.Update();
        break;
    }
    case UIScreenID::eDEFAULT :
    default :
    {
        m_HUDScreen.Update();

        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "UIManager m_ScreenStack is empty. Defaulting to HUD.");
        break;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Draw(SDL_Renderer* renderer)
{
    switch (GetActiveScreenID())
    {
    case UIScreenID::eHud :
    {
        m_HUDScreen.Draw(renderer);
        break;
    }
    case UIScreenID::ePause :
    {
        m_PauseScreen.Draw(renderer);
        break;
    }
    case UIScreenID::eDEFAULT :
    default :
    {
        m_HUDScreen.Draw(renderer);

        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "UI Draw corrupted.");
        break;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::ActivateScreen(UIScreenID screenID)
{
    if (GetActiveScreenID() != screenID)
    {
        m_ScreenStack.push(screenID);
        CallOnShow();
    }
    else
    {
        std::string errorMessage = "Youre attempting to activate a screen that is already active. Current active ScreenID: ";
        errorMessage.append(std::to_string(static_cast<int>(GetActiveScreenID())));

        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::RemoveScreen(UIScreenID screenID)
{
    if (GetActiveScreenID() == screenID)
    {
        m_ScreenStack.pop();
    }
    else
    {
        std::string errorMessage = "Screen youre removing is not current active screen. Current active ScreenID: ";
        errorMessage.append(std::to_string(static_cast<int>(GetActiveScreenID())));
        errorMessage.append(", input screenID: ");
        errorMessage.append(std::to_string(static_cast<int>(screenID)));

        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::CallOnShow()
{
	switch (GetActiveScreenID())
	{
	case UIScreenID::eHud:
	{
		m_HUDScreen.OnShow();
		break;
	}
	case UIScreenID::ePause:
	{
		m_PauseScreen.OnShow();
		break;
	}
	case UIScreenID::eDEFAULT:
	default:
	{
		m_HUDScreen.OnShow();

		Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "UIManager m_ScreenStack is empty. Defaulting to HUD.");
		break;
	}
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
const UI::UIScreenID UIManager::GetActiveScreenID()
{
    return m_ScreenStack.top();
}

}