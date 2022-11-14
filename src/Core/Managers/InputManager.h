#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

namespace CoreManagers
{


enum class InputMappings
{
    // Mouse Actions.
    eMouse1,
    eMouse2,
    eMouse3,

    // Navigation Actions.
    eRight,
    eLeft,
    eUp,
    eDown,
    eRun,

    // Gameplay Actions.
    eInteract,
    eAction,

    // System Actions.
    eESCMenu,
    eTabMenu,

    // Debug Actions.
    eDebug1,
    eDebug2,
    eDebug3,
    eDebug4,

};


struct InputMappingsData
{
    // Debug Keys.
    bool m_F1 = false;
    bool m_F2 = false;
    bool m_F3 = false;
    bool m_F4 = false;

    // Mouse Actions.
    bool m_LeftClicked = false;
    bool m_RightClicked = false;
    bool m_MiddleClicked = false;

    // System Keys.
    bool m_Escape = false;
    bool m_Tab = false;

    // Player Keys.
    bool m_UpArrow = false;
    bool m_DownArrow = false;
    bool m_LeftArrow = false;
    bool m_RightArrow = false;
    bool m_W = false;
    bool m_A = false;
    bool m_S = false;
    bool m_D = false;

    bool m_Space = false;

    // Gameplay Keys.
    bool m_E = false;
    bool m_J = false;
};


class InputManager
{
public:
    InputManager();
    ~InputManager();

    void ProcessInputs();

    bool GetActionPressed(const InputMappings Mapping);
    bool GetActionHeld(const InputMappings Mapping);


private:

    void ResetAllPressedData();

    void OnKeyUpEvent();
    void OnMouseEvent();
    void OnKeyDownEvent();


private:

    SDL_Event* m_SDLEvent;

    InputMappingsData m_InputMappingPressedData;
    InputMappingsData m_InputMappingHeldData;

};

extern InputManager g_InputManager;

}
