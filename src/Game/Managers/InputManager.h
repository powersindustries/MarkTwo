#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

namespace MarkTwo
{

struct MouseButtonData
{
    bool m_LeftClicked;
    bool m_RightClicked;
    bool m_MiddleClicked;
};

struct KeyboardData
{
    // System Keys
    bool m_Escape;
    bool m_Tab;

    // Debug Keys
    bool m_F1;
    bool m_F2;
    bool m_F3;
    bool m_F4;

    // Player Keys
    bool m_UpArrow;
    bool m_DownArrow;
    bool m_LeftArrow;
    bool m_RightArrow;

    bool m_W;
    bool m_A;
    bool m_S;
    bool m_D;
};


class InputManager
{
public:
    InputManager();
    ~InputManager();

    void Refresh();
    void RefreshKeyboardState(SDL_KeyboardEvent& keyboardEvent);

    void ManageMouseButtonState(SDL_MouseButtonEvent& buttonEvent);
    void ManageKeyState(SDL_KeyboardEvent& keyboardEvent);

    // Returns true on button up, false any other time
    MouseButtonData m_MouseButtonData;

    // Returns true while keyboard buttons are pressed, false when they are not
    KeyboardData m_KeyboardHeldData;

    // Returns true on button down, false when they are not
    KeyboardData m_KeyboardPressedData;
};

extern InputManager g_InputManager;
}
