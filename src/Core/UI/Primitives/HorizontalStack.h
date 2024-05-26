#ifndef HorizontalStack_h
#define HorizontalStack_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>

#include "Core/Math/VectorMethods.h"
#include "Core/UI/Types/StackBase.h"

namespace UI
{

class HorizontalStack : public StackBase
{
public:

    void RefreshUI() override;

    void AddChild(UIBase* child) override;
    void SetVisibility(const UIVisibility& visibility) override;


protected:

    void SetPositionNoRefresh(const int x, const int y) override;

};
}

#endif