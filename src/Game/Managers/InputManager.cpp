#include "InputManager.h"
#include "EventManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
InputManager g_InputManager;


// -------------------------------------------------------
// -------------------------------------------------------
InputManager::InputManager()
{
    // Reset Mouse Click states
    m_MouseButtonData.m_LeftClicked = false;
    m_MouseButtonData.m_RightClicked = false;
    m_MouseButtonData.m_MiddleClicked = false;

    // Reset Keyboard Held States
    m_KeyboardHeldData.m_Escape = false;
    m_KeyboardHeldData.m_Tab = false;
    m_KeyboardHeldData.m_F1 = false;
    m_KeyboardHeldData.m_F2 = false;
    m_KeyboardHeldData.m_F3 = false;
    m_KeyboardHeldData.m_F4 = false;

    // Reset Keyboard Click States
    m_KeyboardPressedData.m_Escape = false;
    m_KeyboardPressedData.m_Tab = false;
    m_KeyboardPressedData.m_F1 = false;
    m_KeyboardPressedData.m_F2 = false;
    m_KeyboardPressedData.m_F3 = false;
    m_KeyboardPressedData.m_F4 = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
InputManager::~InputManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::Refresh()
{
    // Reset Mouse Click states
    m_MouseButtonData.m_LeftClicked = false;
    m_MouseButtonData.m_RightClicked = false;
    m_MouseButtonData.m_MiddleClicked = false;

    // Reset Keyboard Click states
    m_KeyboardPressedData.m_Escape = false;
    m_KeyboardPressedData.m_Tab = false;
    m_KeyboardPressedData.m_F1 = false;
    m_KeyboardPressedData.m_F2 = false;
    m_KeyboardPressedData.m_F3 = false;
    m_KeyboardPressedData.m_F4 = false;
    m_KeyboardPressedData.m_UpArrow = false;
    m_KeyboardPressedData.m_DownArrow = false;
    m_KeyboardPressedData.m_LeftArrow = false;
    m_KeyboardPressedData.m_RightArrow = false;
    m_KeyboardPressedData.m_W = false;
    m_KeyboardPressedData.m_A = false;
    m_KeyboardPressedData.m_S = false;
    m_KeyboardPressedData.m_D = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::RefreshKeyboardState(SDL_KeyboardEvent& keyboardEvent)
{
    switch (keyboardEvent.keysym.sym)
    {
    case SDLK_ESCAPE:
    {
        m_KeyboardHeldData.m_Escape = false;
        break;
    }
    case SDLK_TAB:
    {
        m_KeyboardHeldData.m_Tab = false;
        break;
    }
    case SDLK_F1:
    {
        m_KeyboardHeldData.m_F1 = false;
        break;
    }
    case SDLK_F2:
    {
        m_KeyboardHeldData.m_F2 = false;
        break;
    }
    case SDLK_F3:
    {
        m_KeyboardHeldData.m_F3 = false;
        break;
    }
    case SDLK_F4:
    {
        m_KeyboardHeldData.m_F4 = false;
        break;
    }
    case SDLK_UP:
    {
        m_KeyboardHeldData.m_UpArrow = false;
        break;
    }
    case SDLK_DOWN:
    {
        m_KeyboardHeldData.m_DownArrow = false;
        break;
    }
    case SDLK_LEFT:
    {
        m_KeyboardHeldData.m_LeftArrow = false;
        break;
    }
    case SDLK_RIGHT:
    {
        m_KeyboardHeldData.m_RightArrow = false;
        break;
    }
    case SDLK_w:
    {
        m_KeyboardHeldData.m_W = false;
        break;
    }
    case SDLK_a:
    {
        m_KeyboardHeldData.m_A = false;
        break;
    }
    case SDLK_s:
    {
        m_KeyboardHeldData.m_S = false;
        break;
    }
    case SDLK_d:
    {
        m_KeyboardHeldData.m_D = false;
        break;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::ManageMouseButtonState(SDL_MouseButtonEvent& buttonEvent)
{
    m_MouseButtonData.m_LeftClicked = buttonEvent.button == SDL_BUTTON_LEFT;
    m_MouseButtonData.m_RightClicked = buttonEvent.button == SDL_BUTTON_RIGHT;
    m_MouseButtonData.m_MiddleClicked = buttonEvent.button == SDL_BUTTON_MIDDLE;
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::ManageKeyState(SDL_KeyboardEvent& keyboardEvent)
{
    if (keyboardEvent.repeat == 0)
    {
        switch (keyboardEvent.keysym.sym)
        {
        case SDLK_ESCAPE:
        {
            m_KeyboardHeldData.m_Escape = true;
            m_KeyboardPressedData.m_Escape = true;
            break;
        }
        case SDLK_TAB:
        {
            m_KeyboardHeldData.m_Tab = true;
            m_KeyboardPressedData.m_Tab = true;
            break;
        }
        case SDLK_F1:
        {
            m_KeyboardHeldData.m_F1 = true;
            m_KeyboardPressedData.m_F1 = true;
            break;
        }
        case SDLK_F2:
        {
            m_KeyboardHeldData.m_F2 = true;
            m_KeyboardPressedData.m_F2 = true;
            break;
        }
        case SDLK_F3:
        {
            m_KeyboardHeldData.m_F3 = true;
            m_KeyboardPressedData.m_F3 = true;
            break;
        }
        case SDLK_F4:
        {
            m_KeyboardHeldData.m_F4 = true;
            m_KeyboardPressedData.m_F4 = true;

            // Broadcast TestEvent event.
            g_EventManager.Broadcast(Events::eTestEvent);
            break;
        }
        case SDLK_UP:
        {
            m_KeyboardHeldData.m_UpArrow = true;
            m_KeyboardPressedData.m_UpArrow = true;
            break;
        }
        case SDLK_DOWN:
        {
            m_KeyboardHeldData.m_DownArrow = true;
            m_KeyboardPressedData.m_DownArrow = true;
            break;
        }
        case SDLK_LEFT:
        {
            m_KeyboardHeldData.m_LeftArrow = true;
            m_KeyboardPressedData.m_LeftArrow = true;
            break;
        }
        case SDLK_RIGHT:
        {
            m_KeyboardHeldData.m_RightArrow = true;
            m_KeyboardPressedData.m_RightArrow = true;
            break;
        }
        case SDLK_w:
        {
            m_KeyboardHeldData.m_W = true;
            m_KeyboardPressedData.m_W = true;
            break;
        }
        case SDLK_a:
        {
            m_KeyboardHeldData.m_A = true;
            m_KeyboardPressedData.m_A = true;
            break;
        }
        case SDLK_s:
        {
            m_KeyboardHeldData.m_S = true;
            m_KeyboardPressedData.m_S = true;
            break;
        }
        case SDLK_d:
        {
            m_KeyboardHeldData.m_D = true;
            m_KeyboardPressedData.m_D = true;
            break;
        }
        }
    }
}

}