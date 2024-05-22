#include "InputManager.h"
#include "GameGlobals.h"

#define DEFAULT_TIMESTAMP -1

namespace Core
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

    m_bMouseClickAbsorbedByUI = false;
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
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEMOTION:
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
bool InputManager::GetActionPressed(const InputMappings& mapping)
{
    switch (mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingPressedData.m_bLeftClicked;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingPressedData.m_bRightClicked;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingPressedData.m_bMiddleClicked;
    }
    case InputMappings::eMouseMotion:
    {
        return m_InputMappingPressedData.m_bMouseMotion;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingPressedData.m_bEscape;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingPressedData.m_bTab;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingPressedData.m_bD || m_InputMappingPressedData.m_bRightArrow;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingPressedData.m_bA || m_InputMappingPressedData.m_bLeftArrow;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingPressedData.m_bW || m_InputMappingPressedData.m_bUpArrow;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingPressedData.m_bS || m_InputMappingPressedData.m_bDownArrow;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingPressedData.m_bSpace;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingPressedData.m_bE;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingPressedData.m_bLeftClicked || m_InputMappingPressedData.m_bJ;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingPressedData.m_bF1;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingPressedData.m_bF2;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingPressedData.m_bF3;
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


bool InputManager::GetActionHeld(const InputMappings& mapping)
{
    switch (mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bLeftClicked;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bRightClicked;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bMiddleClicked;
    }
    case InputMappings::eMouseMotion:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bMouseMotion;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bEscape;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bTab;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bD || m_InputMappingHeldData.m_InputMappingData.m_bRightArrow;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bA || m_InputMappingHeldData.m_InputMappingData.m_bLeftArrow;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bW || m_InputMappingHeldData.m_InputMappingData.m_bUpArrow;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bS || m_InputMappingHeldData.m_InputMappingData.m_bDownArrow;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bSpace;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bE;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bLeftClicked || m_InputMappingHeldData.m_InputMappingData.m_bJ;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bF1;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bF2;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_bF3;
    }
    case InputMappings::eDebug4:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_F4;
    }
    default:
    {
        return false;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
int64_t InputManager::GetActionHeldTimestamp(const InputMappings& mapping)
{
    switch (mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingHeldData.m_LeftClickedStamp;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingHeldData.m_RightClickedStamp;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingHeldData.m_MiddleClickedStamp;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingHeldData.m_EscapeStamp;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingHeldData.m_TabStamp;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingHeldData.m_DStamp > m_InputMappingHeldData.m_RightArrowStamp ? m_InputMappingHeldData.m_DStamp : m_InputMappingHeldData.m_RightArrowStamp;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingHeldData.m_AStamp > m_InputMappingHeldData.m_LeftArrowStamp ? m_InputMappingHeldData.m_AStamp : m_InputMappingHeldData.m_LeftArrowStamp;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingHeldData.m_WStamp > m_InputMappingHeldData.m_UpArrowStamp ? m_InputMappingHeldData.m_WStamp : m_InputMappingHeldData.m_UpArrowStamp;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingHeldData.m_SStamp > m_InputMappingHeldData.m_DownArrowStamp ? m_InputMappingHeldData.m_SStamp : m_InputMappingHeldData.m_DownArrowStamp;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingHeldData.m_SpaceStamp;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingHeldData.m_EStamp;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingHeldData.m_LeftClickedStamp != DEFAULT_TIMESTAMP ? m_InputMappingHeldData.m_LeftClickedStamp : m_InputMappingHeldData.m_JStamp;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingHeldData.m_F1Stamp;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingHeldData.m_F2Stamp;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingHeldData.m_F3Stamp;
    }
    case InputMappings::eDebug4:
    {
        return m_InputMappingHeldData.m_F4Stamp;
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
    m_InputMappingPressedData.m_bF1 = false;
    m_InputMappingPressedData.m_bF2 = false;
    m_InputMappingPressedData.m_bF3 = false;
    m_InputMappingPressedData.m_F4 = false;
    m_InputMappingPressedData.m_bLeftClicked = false;
    m_InputMappingPressedData.m_bRightClicked = false;
    m_InputMappingPressedData.m_bMiddleClicked = false;
    m_InputMappingPressedData.m_bMouseMotion = false;
    m_InputMappingPressedData.m_bEscape = false;
    m_InputMappingPressedData.m_bTab = false;
    m_InputMappingPressedData.m_bUpArrow = false;
    m_InputMappingPressedData.m_bDownArrow = false;
    m_InputMappingPressedData.m_bLeftArrow = false;
    m_InputMappingPressedData.m_bRightArrow = false;
    m_InputMappingPressedData.m_bSpace = false;
    m_InputMappingPressedData.m_bW = false;
    m_InputMappingPressedData.m_bA = false;
    m_InputMappingPressedData.m_bS = false;
    m_InputMappingPressedData.m_bD = false;
    m_InputMappingPressedData.m_bE = false;
    m_InputMappingPressedData.m_bJ = false;

    m_bMouseClickAbsorbedByUI = false;
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
        m_InputMappingHeldData.m_InputMappingData.m_bEscape = false;
        m_InputMappingHeldData.m_EscapeStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_TAB:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bTab = false;
        m_InputMappingHeldData.m_TabStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F1:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bF1 = false;
        m_InputMappingHeldData.m_F1Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F2:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bF2 = false;
        m_InputMappingHeldData.m_F2Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F3:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bF3 = false;
        m_InputMappingHeldData.m_F3Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F4:
    {
        m_InputMappingHeldData.m_InputMappingData.m_F4 = false;
        m_InputMappingHeldData.m_F4Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_UP:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bUpArrow = false;
        m_InputMappingHeldData.m_UpArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_DOWN:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bDownArrow = false;
        m_InputMappingHeldData.m_DownArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_LEFT:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bLeftArrow = false;
        m_InputMappingHeldData.m_LeftArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_RIGHT:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bRightArrow = false;
        m_InputMappingHeldData.m_RightArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_SPACE:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bSpace = false;
        m_InputMappingHeldData.m_SpaceStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_w:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bW = false;
        m_InputMappingHeldData.m_WStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_a:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bA = false;
        m_InputMappingHeldData.m_AStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_s:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bS = false;
        m_InputMappingHeldData.m_SStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_d:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bD = false;
        m_InputMappingHeldData.m_DStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_e:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bE = false;
        m_InputMappingHeldData.m_EStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_j:
    {
        m_InputMappingHeldData.m_InputMappingData.m_bJ = false;
        m_InputMappingHeldData.m_JStamp = DEFAULT_TIMESTAMP;
        break;
    }
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnMouseEvent()
{
    SDL_MouseButtonEvent& mouseButtonEvent = m_SDLEvent->button;
    m_InputMappingPressedData.m_bLeftClicked = mouseButtonEvent.button == SDL_BUTTON_LEFT;
    m_InputMappingPressedData.m_bRightClicked = mouseButtonEvent.button == SDL_BUTTON_RIGHT;
    m_InputMappingPressedData.m_bMiddleClicked = mouseButtonEvent.button == SDL_BUTTON_MIDDLE;
    m_InputMappingHeldData.m_InputMappingData.m_bLeftClicked = mouseButtonEvent.button == SDL_BUTTON_LEFT;
    m_InputMappingHeldData.m_InputMappingData.m_bRightClicked = mouseButtonEvent.button == SDL_BUTTON_RIGHT;
    m_InputMappingHeldData.m_InputMappingData.m_bMiddleClicked = mouseButtonEvent.button == SDL_BUTTON_MIDDLE;

    SDL_MouseMotionEvent& mouseMotionEvent = m_SDLEvent->motion;
    int32_t xRel = static_cast<int32_t>(mouseMotionEvent.xrel);
    int32_t yRel = static_cast<int32_t>(mouseMotionEvent.yrel);

    uint32_t xRelAbs = static_cast<int32_t>(abs(mouseMotionEvent.xrel));
    uint32_t yRelAbs = static_cast<int32_t>(abs(mouseMotionEvent.yrel));

    m_InputMappingPressedData.m_bMouseMotion = (xRelAbs > 1 && yRelAbs > 1);
    m_InputMappingHeldData.m_InputMappingData.m_bMouseMotion = (xRelAbs > 1 && yRelAbs > 1);
    if (m_InputMappingPressedData.m_bMouseMotion)
    {
        if (xRelAbs == yRelAbs)
        {
            m_MouseMotionData.m_iMotionX = 0;
            m_MouseMotionData.m_iMotionY = 0;
        }
        // Movement in X.
        else if (xRelAbs > yRelAbs)
        {
            m_MouseMotionData.m_iMotionX = xRel;
            m_MouseMotionData.m_iMotionY = 0;
        }
        // Movement in X.
        else
        {
            m_MouseMotionData.m_iMotionX = 0;
            m_MouseMotionData.m_iMotionY = yRel;
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnKeyDownEvent()
{
    SDL_KeyboardEvent& keyboardEvent = m_SDLEvent->key;

    if (keyboardEvent.repeat == 0)
    {
        switch (keyboardEvent.keysym.sym)
        {
        case SDLK_ESCAPE:
        {
            m_InputMappingPressedData.m_bEscape = true;

            m_InputMappingHeldData.m_InputMappingData.m_bEscape = true;
            if (m_InputMappingHeldData.m_EscapeStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_EscapeStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_TAB:
        {
            m_InputMappingPressedData.m_bTab = true;

            m_InputMappingHeldData.m_InputMappingData.m_bTab = true;
            if (m_InputMappingHeldData.m_TabStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_TabStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F1:
        {
            m_InputMappingPressedData.m_bF1 = true;

            m_InputMappingHeldData.m_InputMappingData.m_bF1 = true;
            if (m_InputMappingHeldData.m_F1Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F1Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F2:
        {
            m_InputMappingPressedData.m_bF2 = true;

            m_InputMappingHeldData.m_InputMappingData.m_bF2 = true;
            if (m_InputMappingHeldData.m_F2Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F2Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F3:
        {
            m_InputMappingPressedData.m_bF3 = true;

            m_InputMappingHeldData.m_InputMappingData.m_bF3 = true;
            if (m_InputMappingHeldData.m_F3Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F3Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F4:
        {
            m_InputMappingPressedData.m_F4 = true;

            m_InputMappingHeldData.m_InputMappingData.m_F4 = true;
            if (m_InputMappingHeldData.m_F4Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F4Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_UP:
        {
            m_InputMappingPressedData.m_bUpArrow = true;
            m_InputMappingHeldData.m_InputMappingData.m_bUpArrow = true;
            if (m_InputMappingHeldData.m_UpArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_UpArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_DOWN:
        {
            m_InputMappingPressedData.m_bDownArrow = true;

            m_InputMappingHeldData.m_InputMappingData.m_bDownArrow = true;
            if (m_InputMappingHeldData.m_DownArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_DownArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_LEFT:
        {
            m_InputMappingPressedData.m_bLeftArrow = true;

            m_InputMappingHeldData.m_InputMappingData.m_bLeftArrow = true;
            if (m_InputMappingHeldData.m_LeftArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_LeftArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_RIGHT:
        {
            m_InputMappingPressedData.m_bRightArrow = true;

            m_InputMappingHeldData.m_InputMappingData.m_bRightArrow = true;
            if (m_InputMappingHeldData.m_RightArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_RightArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_SPACE:
        {
            m_InputMappingPressedData.m_bSpace = true;

            m_InputMappingHeldData.m_InputMappingData.m_bSpace = true;
            if (m_InputMappingHeldData.m_SpaceStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_SpaceStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_w:
        {
            m_InputMappingPressedData.m_bW = true;

            m_InputMappingHeldData.m_InputMappingData.m_bW = true;
            if (m_InputMappingHeldData.m_WStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_WStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_a:
        {
            m_InputMappingPressedData.m_bA = true;

            m_InputMappingHeldData.m_InputMappingData.m_bA = true;
            if (m_InputMappingHeldData.m_AStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_AStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_s:
        {
            m_InputMappingPressedData.m_bS = true;

            m_InputMappingHeldData.m_InputMappingData.m_bS = true;
            if (m_InputMappingHeldData.m_SStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_SStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_d:
        {
            m_InputMappingPressedData.m_bD = true;

            m_InputMappingHeldData.m_InputMappingData.m_bD = true;
            if (m_InputMappingHeldData.m_DStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_DStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_e:
        {
            m_InputMappingPressedData.m_bE = true;

            m_InputMappingHeldData.m_InputMappingData.m_bE = true;
            if (m_InputMappingHeldData.m_EStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_EStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_j:
        {
            m_InputMappingPressedData.m_bJ = true;

            m_InputMappingHeldData.m_InputMappingData.m_bJ = true;
            if (m_InputMappingHeldData.m_JStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_JStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        }
    }
}

}