#include "InputManager.h"
#include "Game/Managers/EventManager.h"
#include "GameGlobals.h"

namespace CoreManagers
{


// -------------------------------------------------------
// -------------------------------------------------------
InputManager g_InputManager;


// -------------------------------------------------------
// -------------------------------------------------------
InputManager::InputManager()
    : m_SDLEvent(nullptr)
{
    m_SDLEvent = new SDL_Event;
}


// -------------------------------------------------------
// -------------------------------------------------------
InputManager::~InputManager()
{
    delete m_SDLEvent;
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::ProcessInputs()
{
    ResetAllPressedData();

    while (SDL_PollEvent(m_SDLEvent))
    {
        switch (m_SDLEvent->type)
        {
        case SDL_QUIT:
        {
            MarkTwo::g_GameGlobals.m_bGameRunning = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            OnKeyDownEvent();
            break;
        }
        case SDL_KEYUP:
        {
            OnKeyUpEvent();
            break;
        }
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
        {
            OnMouseEvent();
            break;
        }
        default:
            break;
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
bool InputManager::GetActionPressed(const InputMappings Mapping)
{
    switch (Mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingPressedData.m_LeftClicked;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingPressedData.m_RightClicked;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingPressedData.m_MiddleClicked;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingPressedData.m_Escape;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingPressedData.m_Tab;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingPressedData.m_D || m_InputMappingPressedData.m_RightArrow;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingPressedData.m_A || m_InputMappingPressedData.m_LeftArrow;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingPressedData.m_W || m_InputMappingPressedData.m_UpArrow;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingPressedData.m_S || m_InputMappingPressedData.m_DownArrow;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingPressedData.m_Space;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingPressedData.m_E;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingPressedData.m_LeftClicked || m_InputMappingPressedData.m_J;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingPressedData.m_F1;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingPressedData.m_F2;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingPressedData.m_F3;
    }
    case InputMappings::eDebug4:
    {
        return m_InputMappingPressedData.m_F4;
    }
    default:
    {
        return false;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
bool InputManager::GetActionHeld(const InputMappings Mapping)
{
    switch (Mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingHeldData.m_LeftClicked;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingHeldData.m_RightClicked;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingHeldData.m_MiddleClicked;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingHeldData.m_Escape;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingHeldData.m_Tab;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingHeldData.m_D || m_InputMappingHeldData.m_RightArrow;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingHeldData.m_A || m_InputMappingHeldData.m_LeftArrow;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingHeldData.m_W || m_InputMappingHeldData.m_UpArrow;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingHeldData.m_S || m_InputMappingHeldData.m_DownArrow;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingHeldData.m_Space;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingHeldData.m_E;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingHeldData.m_LeftClicked || m_InputMappingHeldData.m_J;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingHeldData.m_F1;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingHeldData.m_F2;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingHeldData.m_F3;
    }
    case InputMappings::eDebug4:
    {
        return m_InputMappingHeldData.m_F4;
    }
    default:
    {
        return false;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::ResetAllPressedData()
{
    m_InputMappingPressedData.m_F1            = false;
    m_InputMappingPressedData.m_F2            = false;
    m_InputMappingPressedData.m_F3            = false;
    m_InputMappingPressedData.m_F4            = false;
    m_InputMappingPressedData.m_LeftClicked   = false;
    m_InputMappingPressedData.m_RightClicked  = false;
    m_InputMappingPressedData.m_MiddleClicked = false;
    m_InputMappingPressedData.m_Escape        = false;
    m_InputMappingPressedData.m_Tab           = false;
    m_InputMappingPressedData.m_UpArrow       = false;
    m_InputMappingPressedData.m_DownArrow     = false;
    m_InputMappingPressedData.m_LeftArrow     = false;
    m_InputMappingPressedData.m_RightArrow    = false;
    m_InputMappingPressedData.m_Space         = false;
    m_InputMappingPressedData.m_W             = false;
    m_InputMappingPressedData.m_A             = false;
    m_InputMappingPressedData.m_S             = false;
    m_InputMappingPressedData.m_D             = false;
    m_InputMappingPressedData.m_E             = false;
    m_InputMappingPressedData.m_J             = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnKeyUpEvent()
{
    SDL_KeyboardEvent& currKeyboardEvent = m_SDLEvent->key;
    switch (currKeyboardEvent.keysym.sym)
    {
    case SDLK_ESCAPE:
    {
        m_InputMappingHeldData.m_Escape = false;
        break;
    }
    case SDLK_TAB:
    {
        m_InputMappingHeldData.m_Tab = false;
        break;
    }
    case SDLK_F1:
    {
        m_InputMappingHeldData.m_F1 = false;
        break;
    }
    case SDLK_F2:
    {
        m_InputMappingHeldData.m_F2 = false;
        break;
    }
    case SDLK_F3:
    {
        m_InputMappingHeldData.m_F3 = false;
        break;
    }
    case SDLK_F4:
    {
        m_InputMappingHeldData.m_F4 = false;
        break;
    }
    case SDLK_UP:
    {
        m_InputMappingHeldData.m_UpArrow = false;
        break;
    }
    case SDLK_DOWN:
    {
        m_InputMappingHeldData.m_DownArrow = false;
        break;
    }
    case SDLK_LEFT:
    {
        m_InputMappingHeldData.m_LeftArrow = false;
        break;
    }
    case SDLK_RIGHT:
    {
        m_InputMappingHeldData.m_RightArrow = false;
        break;
    }
    case SDLK_SPACE:
    {
        m_InputMappingHeldData.m_Space = false;
        break;
    }
    case SDLK_w:
    {
        m_InputMappingHeldData.m_W = false;
        break;
    }
    case SDLK_a:
    {
        m_InputMappingHeldData.m_A = false;
        break;
    }
    case SDLK_s:
    {
        m_InputMappingHeldData.m_S = false;
        break;
    }
    case SDLK_d:
    {
        m_InputMappingHeldData.m_D = false;
        break;
    }
    case SDLK_e:
    {
        m_InputMappingHeldData.m_E = false;
        break;
    }
    case SDLK_j:
    {
        m_InputMappingHeldData.m_J = false;
        break;
    }
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnMouseEvent()
{
    SDL_MouseButtonEvent& buttonEvent = m_SDLEvent->button;

    m_InputMappingPressedData.m_LeftClicked   = buttonEvent.button == SDL_BUTTON_LEFT;
    m_InputMappingPressedData.m_RightClicked  = buttonEvent.button == SDL_BUTTON_RIGHT;
    m_InputMappingPressedData.m_MiddleClicked = buttonEvent.button == SDL_BUTTON_MIDDLE;

    m_InputMappingHeldData.m_LeftClicked   = buttonEvent.button == SDL_BUTTON_LEFT;
    m_InputMappingHeldData.m_RightClicked  = buttonEvent.button == SDL_BUTTON_RIGHT;
    m_InputMappingHeldData.m_MiddleClicked = buttonEvent.button == SDL_BUTTON_MIDDLE;
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnKeyDownEvent()
{
    SDL_KeyboardEvent& keyboardEvent = m_SDLEvent->key;

    if (keyboardEvent.repeat == 0)
    {
        if (keyboardEvent.keysym.sym == SDLK_BACKSPACE)
        {
            MarkTwo::g_GameGlobals.m_bGameRunning = false;
            return;
        }

        switch (keyboardEvent.keysym.sym)
        {
        case SDLK_ESCAPE:
        {
            m_InputMappingPressedData.m_Escape = true;
            m_InputMappingHeldData.m_Escape = true;
            break;
        }
        case SDLK_TAB:
        {
            m_InputMappingPressedData.m_Tab = true;
            m_InputMappingHeldData.m_Tab = true;
            break;
        }
        case SDLK_F1:
        {
            m_InputMappingPressedData.m_F1 = true;
            m_InputMappingHeldData.m_F1 = true;
            break;
        }
        case SDLK_F2:
        {
            m_InputMappingPressedData.m_F2 = true;
            m_InputMappingHeldData.m_F2 = true;
            break;
        }
        case SDLK_F3:
        {
            m_InputMappingPressedData.m_F3 = true;
            m_InputMappingHeldData.m_F3 = true;
            break;
        }
        case SDLK_F4:
        {
            m_InputMappingPressedData.m_F4 = true;
            m_InputMappingHeldData.m_F4 = true;
            break;
        }
        case SDLK_UP:
        {
            m_InputMappingPressedData.m_UpArrow = true;
            m_InputMappingHeldData.m_UpArrow = true;
            break;
        }
        case SDLK_DOWN:
        {
            m_InputMappingPressedData.m_DownArrow = true;
            m_InputMappingHeldData.m_DownArrow = true;
            break;
        }
        case SDLK_LEFT:
        {
            m_InputMappingPressedData.m_LeftArrow = true;
            m_InputMappingHeldData.m_LeftArrow = true;
            break;
        }
        case SDLK_RIGHT:
        {
            m_InputMappingPressedData.m_RightArrow = true;
            m_InputMappingHeldData.m_RightArrow = true;
            break;
        }
        case SDLK_SPACE:
        {
            m_InputMappingPressedData.m_Space = true;
            m_InputMappingHeldData.m_Space = true;
            break;
        }
        case SDLK_w:
        {
            m_InputMappingPressedData.m_W = true;
            m_InputMappingHeldData.m_W = true;
            break;
        }
        case SDLK_a:
        {
            m_InputMappingPressedData.m_A = true;
            m_InputMappingHeldData.m_A = true;
            break;
        }
        case SDLK_s:
        {
            m_InputMappingPressedData.m_S = true;
            m_InputMappingHeldData.m_S = true;
            break;
        }
        case SDLK_d:
        {
            m_InputMappingPressedData.m_D = true;
            m_InputMappingHeldData.m_D = true;
            break;
        }
        case SDLK_e:
        {
            m_InputMappingPressedData.m_E = true;
            m_InputMappingHeldData.m_E = true;
            break;
        }
        case SDLK_j:
        {
            m_InputMappingPressedData.m_J = true;
            m_InputMappingHeldData.m_J = true;
            break;
        }
        }
    }
}

}