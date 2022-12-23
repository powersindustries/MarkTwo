#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/StackPanel.h"
#include "Core/UI/Types/Button.h"

using namespace CoreUI;

namespace MarkTwo
{
class HUDScreen : public UIScreenBase
{
public:
    HUDScreen();
    ~HUDScreen();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void Initialize();
    void OnShow() {}


private:
    Box m_TitleBox;
    TextBlock m_Title;

    Box m_PlayerBox;
    TextBlock m_PlayerText;

    Box m_DirectionsBox;
    StackPanel m_DirectionsStack;
    TextBlock m_DirectionTitle;
    TextBlock m_MovementText;
    TextBlock m_PauseText;
    TextBlock m_DebugText;
    TextBlock m_KillGameText;

    TextBlock m_EventInfoText;

};
}