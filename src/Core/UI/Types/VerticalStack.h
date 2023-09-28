#ifndef VerticalStack_h
#define VerticalStack_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>

#include "../UICore.h"
#include "Core/Math/VectorMethods.h"

namespace UI
{

class VerticalStack : public UIBase
{
public:
    VerticalStack();
    ~VerticalStack();

    void Draw(SDL_Renderer* renderer) override;
    void SetStyle(uint32_t uiStyleID) override;
    void SetOffset(int xOffset, int yOffset) override;

    void RefreshUI() override;

    void AddChild(UIBase* child);
    void ClearChildren();

    void SetVisibility(UIVisibility visibility);
    void SetPadding(int padding);


private:

    void SetPositionNoRefresh(const int x, const int y) override;


public:

	std::vector<UIBase*> m_Children;

	int m_iPadding;

};
}

#endif