#ifndef HUDScreen_h
#define HUDScreen_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/UIScreenBase.h"
#include "Core/UI/Primitives/Box.h"
#include "Core/UI/Primitives/TextBlock.h"
#include "Core/UI/Primitives/VerticalStack.h"
#include "Core/UI/Types/Widget.h"

using namespace UI;

namespace MarkTwo
{
class HUDScreen : public UIScreenBase
{
public:

    HUDScreen();

    void Initialize() override;
    void Update() override;
    void Draw(SDL_Renderer* renderer) override;
    void RemoveSelf()override;


private:

    UI::Widget* m_Widget = nullptr;

//    Box m_TitleBox;
//    TextBlock m_Title;
//
//    Box m_PlayerBox;
//    TextBlock m_PlayerText;
//
//    Box m_DirectionsBox;
//
//    VerticalStack m_DirectionsStack;
//
//    TextBlock m_DirectionTitle;
//    TextBlock m_MovementText;
//    TextBlock m_PauseText;
//    TextBlock m_DebugText;
//    TextBlock m_KillGameText;
//
//    TextBlock m_EventInfoText;

};
}

#endif