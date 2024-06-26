#include "PlayerMovement.h"
#include "Player.h"
#include "Core/Managers/InputManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
PlayerMovement::PlayerMovement()
{
    m_bPlayerMoving = false;
    m_Direction = Direction::eDown;
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerMovement::Update(const float deltaTime)
{
    m_bPlayerMoving = false;

    if (Core::g_InputManager.GetActionHeld(Core::InputMappings::eUp))
    {
        m_Direction = Direction::eUp;
        m_bPlayerMoving = true;
    }
    else if (Core::g_InputManager.GetActionHeld(Core::InputMappings::eDown))
    {
        m_Direction = Direction::eDown;
        m_bPlayerMoving = true;
    }
    else if (Core::g_InputManager.GetActionHeld(Core::InputMappings::eLeft))
    {
        m_Direction = Direction::eLeft;
        m_bPlayerMoving = true;
    }
    else if (Core::g_InputManager.GetActionHeld(Core::InputMappings::eRight))
    {
        m_Direction = Direction::eRight;
        m_bPlayerMoving = true;
    }

    if (m_bPlayerMoving)
    {
        switch (m_Direction)
        {
        case Direction::eUp:
        {
            g_Player.SetPlayerPositionY(g_Player.GetPlayerRectangle().y - m_iPlayerSpeed);
            break;
        }
        case Direction::eDown:
        {
            g_Player.SetPlayerPositionY(g_Player.GetPlayerRectangle().y + m_iPlayerSpeed);
            break;
        }
        case Direction::eLeft:
        {
            g_Player.SetPlayerPositionX(g_Player.GetPlayerRectangle().x - m_iPlayerSpeed);
            break;
        }
        case Direction::eRight:
        {
            g_Player.SetPlayerPositionX(g_Player.GetPlayerRectangle().x + m_iPlayerSpeed);
            break;
        }
        default:
            break;
        }
    }
}

}