#include "FrontendManager.h"

#include "Core/Systems/Systems.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
FrontendManager g_FrontendManager;


// -------------------------------------------------------
// -------------------------------------------------------
FrontendManager::FrontendManager()
{
    // Default add HUD UI Screen to stack.
    m_ScreenStack.push(m_HUDScreen.m_sScreenID);
}


// -------------------------------------------------------
// -------------------------------------------------------
void FrontendManager::Initialize()
{
    m_HUDScreen.Initialize();
    m_PauseScreen.Initialize();

    m_ScreenLookupMap.insert({m_HUDScreen.m_sScreenID, &m_HUDScreen});
    m_ScreenLookupMap.insert({m_PauseScreen.m_sScreenID, &m_PauseScreen});

    m_sPauseMenuScreenID = m_PauseScreen.m_sScreenID;
    m_sHUDScreenID = m_HUDScreen.m_sScreenID;
}


// -------------------------------------------------------
// -------------------------------------------------------
void FrontendManager::Update()
{
    const std::string activeScreenId = GetActiveScreenID();
    if (m_ScreenLookupMap.find(activeScreenId) != m_ScreenLookupMap.end())
    {
        m_ScreenLookupMap[activeScreenId]->Update();
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "FrontendManager m_ScreenStack is empty. Defaulting to HUD.");
        m_HUDScreen.Update();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void FrontendManager::Draw(SDL_Renderer *renderer)
{
    const std::string activeScreenId = GetActiveScreenID();
    if (m_ScreenLookupMap.find(activeScreenId) != m_ScreenLookupMap.end())
    {
        m_ScreenLookupMap[activeScreenId]->Draw(renderer);
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "FrontendManager m_ScreenStack is empty. Defaulting to HUD.");
        m_HUDScreen.Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void FrontendManager::ActivateScreen(const std::string& screenID)
{
    if (GetActiveScreenID() != screenID)
    {
        m_ScreenStack.push(screenID);
        CallOnShow();
    }
    else
    {
        std::string errorMessage = "Youre attempting to activate a screen that is already active. Current active ScreenID: ";
        errorMessage.append(screenID);

        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void FrontendManager::RemoveScreen(const std::string& screenID)
{
    if (GetActiveScreenID() == screenID)
    {
        m_ScreenStack.pop();
    }
    else
    {
        std::string errorMessage = "Screen youre removing is not current active screen. Current active ScreenID: ";
        errorMessage.append(GetActiveScreenID());
        errorMessage.append(", input screenID: ");
        errorMessage.append(screenID);

        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void FrontendManager::CallOnShow()
{
    const std::string& activeScreenId = GetActiveScreenID();
    if (m_ScreenLookupMap.find(activeScreenId) != m_ScreenLookupMap.end())
    {
        m_ScreenLookupMap[activeScreenId]->OnShow();
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "FrontendManager m_ScreenStack is empty. Defaulting to HUD.");
        m_HUDScreen.OnShow();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
const std::string &FrontendManager::GetActiveScreenID()
{
    return m_ScreenStack.top();
}

}