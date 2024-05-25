#include "HUDScreen.h"
#include "../Managers/FrontendManager.h"
#include "Core/UI/UIManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
HUDScreen::HUDScreen()
{
    m_sScreenId = "hud";
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Initialize()
{
    m_Widget = UI::g_UIManager.GetWidgetById("w_hud_screen");

    TextBlock* versionTextblock = dynamic_cast<TextBlock*>(UI::g_UIManager.GetPrimitiveById("version_textblock"));
    assert(versionTextblock);

    const std::string versionText = versionTextblock->GetText() + VERSION_NUMBER;
    versionTextblock->SetText(versionText);

    Box* versionBox = dynamic_cast<Box*>(UI::g_UIManager.GetPrimitiveById("version_box"));
    assert(versionBox);

    versionBox->SetSize(versionTextblock->GetWidth() + 25, versionTextblock->GetHeight() + 50);
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Update()
{
    m_Widget->Update();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Draw(SDL_Renderer* renderer)
{
    m_Widget->Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::RemoveSelf()
{
    g_FrontendManager.RemoveScreen(m_sScreenId);
}

}