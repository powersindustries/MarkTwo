#include "UIScreenBase.h"
#include "Game/Managers/EventManager.h"

namespace UI{


// -------------------------------------------------------
// -------------------------------------------------------
void UIScreenBase::Initialize()
{
    MarkTwo::g_EventManager.Subscribe(MarkTwo::Events::eDebugUIHotReload, [this](){ UIScreenBase::OnDebugUIHotReloadCalled(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIScreenBase::OnDebugUIHotReloadCalled()
{
    HotReloadUI();
}

}

