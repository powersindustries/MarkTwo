#ifndef PauseScreen_h
#define PauseScreen_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/UIScreenBase.h"
#include "Core/UI/Primitives/Box.h"
#include "Core/UI/Primitives/TextBlock.h"
#include "Core/UI/Primitives/VerticalStack.h"
#include "Core/UI/Primitives/Button.h"
#include "Core/UI/Types/Widget.h"

using namespace UI;

namespace MarkTwo
{
class PauseScreen : public UIScreenBase
{
public:

    PauseScreen();

    void Initialize() override;

    void Update() override;
    void Draw(SDL_Renderer* renderer) override;
    void RemoveSelf() override;

    void HotReloadUI() override;


private:

    const std::string m_sWidgetId = "w_pause_screen";

    UI::Widget* m_Widget = nullptr;
    UI::Button* m_ReturnButton = nullptr;
    UI::Button* m_QuitButton = nullptr;

};
}

#endif