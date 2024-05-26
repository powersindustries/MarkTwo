#include "UIScreenBase.h"
#include "Core/Managers/EventManager.h"
#include "Core/UI/UIManager.h"

namespace UI{


// -------------------------------------------------------
// -------------------------------------------------------
void UIScreenBase::Initialize()
{
    Core::g_EventManager.Subscribe(UI_DEBUG_EVENT_ID, [this](){ UIScreenBase::OnDebugUIHotReloadCalled(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIScreenBase::OnDebugUIHotReloadCalled()
{
    HotReloadUI();
}

}

