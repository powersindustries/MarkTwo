#ifndef Widget_H
#define Widget_H

#include <string>
#include <vector>
#include <unordered_map>
#include "UIBase.h"

namespace UI
{

// Widget container for an entire screen of primitives.
// This data is populated from XML markup files.
class Widget
{
public:

    Widget(const std::string& id);

    void Update();
    void Draw(SDL_Renderer* renderer);
    void AddPrimitive(UIBase* primitive);
    UIBase* GetPrimitiveById(const std::string& primitiveId);

    inline std::string GetId() { return m_sId; };


private:

    std::string m_sId;

    std::vector<UIBase*> m_vDrawPrimitives;
    std::unordered_map<std::string, UIBase*> m_PrimitiveSearchMap;

};

}

#endif
