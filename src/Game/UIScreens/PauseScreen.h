#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Button.h"
#include "Core/UI/Types/VerticalStack.h"
#include "Core/UI/UIScreenBase.h"

using namespace UI;

namespace MarkTwo
{
class PauseScreen : public UIScreenBase
{
public:
    PauseScreen();
    ~PauseScreen();

    void Initialize();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void OnShow();
    void RemoveSelf();


private:

    Box m_BackgroundBox;
    TextBlock m_Title;
    TextBlock m_EngineText;

    VerticalStack m_Stack;

    Button m_ReturnToGameButton;
    Button m_QuitGameButton;

};
}