#ifndef Box_h
#define Box_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "Core/UI/Types/UIBase.h"
#include "Core/UI/Types/StackBase.h"

namespace UI
{

// Note: Box type is very similar to the VerticalBox type with a few differences.
class Box : public StackBase
{
public:

    void Draw(SDL_Renderer* renderer) override;
    void RefreshUI() override;

    void AddChild(UIBase* child) override;
    void SetMargin(const Margin& margin);


private:

    void SetPositionNoRefresh(const int x, const int y) override;


protected:

    // Spacing around the content and the box edges.
    Margin m_Margin;

    static int m_iUniqueId;

};
}

#endif