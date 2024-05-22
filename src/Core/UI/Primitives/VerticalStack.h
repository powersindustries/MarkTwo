#ifndef VerticalStack_h
#define VerticalStack_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>

#include "Core/Math/VectorMethods.h"
#include "Core/UI/Types/StackBase.h"

namespace UI
{

class VerticalStack : public StackBase
{
public:

    void Draw(SDL_Renderer* renderer) override;
    void RefreshUI() override;

    void AddChild(UIBase* child) override;
    void SetVisibility(const UIVisibility& visibility) override;


private:

    void SetPositionNoRefresh(const int x, const int y) override;

    friend class Box;

};
}

#endif