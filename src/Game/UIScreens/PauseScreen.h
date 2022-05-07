#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "Core/UI/Types/StackPanel.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Button.h"

using namespace CoreUI;

namespace MarkTwo
{
class PauseScreen : public UIScreenBase
{
public:
    PauseScreen();
    ~PauseScreen();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void Initialize();


private:
    StackPanel m_StackPanel;

    Box m_BackgroundBox;
    TextBlock m_Title;
    TextBlock m_EngineText;

    Button m_ReturnToGameButton;
    Button m_QuitGameButton;

};
}