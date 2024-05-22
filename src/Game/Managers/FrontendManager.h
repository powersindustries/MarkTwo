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

    const std::string& GetActiveScreenID();
    void ActivateScreen(const std::string& screenID);

    void RemoveScreen(const std::string& screenID);

    // Getters for popular screens referenced throughout the games.
    inline const std::string& GetHUDScreenID() { return m_sHUDScreenID; }
    inline const std::string& GetPauseMenuScreenID() { return m_sPauseMenuScreenID; }


private:

    void CallOnShow();


private:

    std::unordered_map<std::string, UIScreenBase*> m_ScreenLookupMap;

    std::stack<std::string> m_ScreenStack;

    std::string m_sHUDScreenID;
    std::string m_sPauseMenuScreenID;

    HUDScreen m_HUDScreen;
    PauseScreen m_PauseScreen;

};

extern FrontendManager g_FrontendManager;
}

#endif