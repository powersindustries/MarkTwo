#ifndef Box_h
#define Box_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "Core/UI/Types/UIBase.h"
#include "VerticalStack.h"

namespace UI
{
class Box : public UIBase
{
public:

    Box();

    void Draw(SDL_Renderer* renderer) override;
    void RefreshUI() override;

    void AddChild(UIBase* child);
    void SetVisibility(const UIVisibility& visibility) override;

    void SetMargin(const Margin& margin);

protected:

    // Spacing around the content and the box edges.
    Margin m_Margin;

    VerticalStack* m_Stack;

};
}

#endif