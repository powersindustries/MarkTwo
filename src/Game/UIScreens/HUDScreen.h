#ifndef HUDScreen_h
#define HUDScreen_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/VerticalStack.h"
#include "Core/UI/Types/HorizontalStack.h"
#include "Core/UI/UIScreenBase.h"

using namespace UI;

namespace MarkTwo
{
class HUDScreen : public UIScreenBase
{
public:
    HUDScreen();
    ~HUDScreen();

    void Initialize() override;
    void Update() override;
    void Draw(SDL_Renderer* renderer) override;
    void OnShow() override;
    void RemoveSelf()override;


private:
 
    Box m_TitleBox;
    TextBlock m_Title;

    Box m_PlayerBox;
    TextBlock m_PlayerText;

    Box m_DirectionsBox;

    VerticalStack m_DirectionsStack;

    TextBlock m_DirectionTitle;
    TextBlock m_MovementText;
    TextBlock m_PauseText;
    TextBlock m_DebugText;
    TextBlock m_KillGameText;

    TextBlock m_EventInfoText;

};
}

#endif