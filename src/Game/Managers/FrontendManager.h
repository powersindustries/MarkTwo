#ifndef UIManager_h
#define UIManager_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <stack>
#include <unordered_map>

#include "Core/UI/Types/UIScreenBase.h"
#include "Game/UIScreens/HUDScreen.h"
#include "Game/UIScreens/PauseScreen.h"

namespace MarkTwo
{

class FrontendManager
{
public:

    FrontendManager();

    void Initialize();

    void Update();
    void Draw(SDL_Renderer* renderer);

    const std::string& GetActiveScreenId();
    void ActivateScreen(const std::string& screenId);

    void RemoveScreen(const std::string& screenId);

    // Getters for popular screens referenced throughout the games.
    inline const std::string& GetHUDScreenId() { return m_sHUDScreenId; }
    inline const std::string& GetPauseMenuScreenId() { return m_sPauseMenuScreenId; }


private:

    void CallOnShow();


private:

    std::unordered_map<std::string, UIScreenBase*> m_ScreenLookupMap;

    std::stack<std::string> m_ScreenStack;

    std::string m_sHUDScreenId;
    std::string m_sPauseMenuScreenId;

    HUDScreen m_HUDScreen;
    PauseScreen m_PauseScreen;

};

extern FrontendManager g_FrontendManager;
}

#endif