#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "Game/UIScreens/HUDScreen.h"
#include "Game/UIScreens/PauseScreen.h"

namespace MarkTwo
{


enum class ActiveScreen
{
    eHud,
    ePause
};


class UIManager
{
public:
    UIManager();
    ~UIManager();

    void InitializeUIScreens();

    void Update();
    void Draw(SDL_Renderer* renderer);

    void ActivatePauseMenu();

    ActiveScreen m_ActiveScreen;


private:
    HUDScreen m_HUDScreen;
    PauseScreen m_PauseScreen;
};

extern UIManager g_UIManager;
}