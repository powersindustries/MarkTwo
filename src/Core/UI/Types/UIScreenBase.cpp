#include "UIScreenBase.h"
#include "Game/Managers/EventManager.h"
#include "Core/UI/UIManager.h"

namespace UI{


// -------------------------------------------------------
// -------------------------------------------------------
void UIScreenBase::Initialize()
{
    MarkTwo::g_EventManager.Subscribe(UI_DEBUG_EVENT_ID, [this](){ UIScreenBase::OnDebugUIHotReloadCalled(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIScreenBase::OnDebugUIHotReloadCalled()
{
    HotReloadUI();
}

}

