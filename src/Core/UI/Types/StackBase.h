#ifndef StackBase_H
#define StackBase_H

#include <vector>
#include "UIBase.h"

namespace UI
{

class StackBase : public UIBase
{
public:

    StackBase();

    void Update() override;
    void Draw(SDL_Renderer* renderer) override;

    virtual void AddChild(UIBase* child) = 0;
    void ClearChildren();

    void SetPadding(const int padding);


protected:

    std::vector<UIBase*> m_Children;

    int m_iPadding;

};

}

#endif