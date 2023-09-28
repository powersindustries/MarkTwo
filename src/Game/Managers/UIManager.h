#ifndef UIManager_h
#define UIManager_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <stack>

#include "Core/UI/UIScreenBase.h"
#include "Game/UIScreens/HUDScreen.h"
#include "Game/UIScreens/PauseScreen.h"

namespace MarkTwo
{

class UIManager
{
public:
    UIManager();
    ~UIManager();

    void Initialize();

    void Update();
    void Draw(SDL_Renderer* renderer);

    const UIScreenID GetActiveScreenID();
    void ActivateScreen(UIScreenID screenID);

    void RemoveScreen(UIScreenID screenID);


private:

    void CallOnShow();


private:

    std::stack<UIScreenID> m_ScreenStack;

    HUDScreen m_HUDScreen;
    PauseScreen m_PauseScreen;

};

extern UIManager g_UIManager;
}

#endif