#include <cassert>
#include "Widget.h"
#include "Core/Systems/Logging.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
Widget::Widget(const std::string& id)
{
    m_sId = id;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Widget::Update()
{
    const uint8_t primitivesSize = static_cast<uint8_t>(m_vDrawPrimitives.size());
    for (int x = 0; x < primitivesSize; ++x)
    {
        UIBase* currPrimitive = m_vDrawPrimitives[x];
        assert(currPrimitive);

        currPrimitive->Update();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Widget::Draw(SDL_Renderer* renderer)
{
    const uint8_t primitivesSize = static_cast<uint8_t>(m_vDrawPrimitives.size());
    for (int x = 0; x < primitivesSize; ++x)
    {
        UIBase* currPrimitive = m_vDrawPrimitives[x];
        assert(currPrimitive);

        currPrimitive->Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Widget::AddPrimitive(UIBase* primitive)
{
    assert(primitive);

    m_vDrawPrimitives.push_back(primitive);
    m_PrimitiveSearchMap.insert( {primitive->m_sId, primitive } );
}


// -------------------------------------------------------
// -------------------------------------------------------
UIBase* Widget::GetPrimitiveById(const std::string& primitiveId)
{
    // Try and grab the primitive from the base widget.
    UIBase* primitive = m_PrimitiveSearchMap[primitiveId];
    if (primitive)
    {
        return primitive;
    }

    Core::SYSTEMS_LOG(Core::LoggingLevel::eError,
                      "Primitive id: " + primitiveId + " does not exist in widget " + GetId());
    return nullptr;
}

}