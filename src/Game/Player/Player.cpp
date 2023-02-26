#include "Player.h"
#include "GameGlobals.h"
#include "Core/Systems/Systems.h"
#include "../Managers/EventManager.h"
#include "Core/Managers/InputManager.h"
#include "Core/Managers/SoundManager.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
Player g_Player;


// -------------------------------------------------------
// -------------------------------------------------------
Player::Player()
    : m_PlayerSprite(nullptr)
{
    m_PlayerRectangle.x = 100;
    m_PlayerRectangle.y = 100;
    m_PlayerRectangle.w = 32;
    m_PlayerRectangle.h = 32;
}


// -------------------------------------------------------
// -------------------------------------------------------
Player::~Player()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::InitializePlayer()
{
    // Initialize Player Sprite
    m_PlayerSprite = new Sprite(CoreSystems::StringToHash32(CoreTypes::String("txt_Chopper")), 90);

    // Subscribe to TestEvent
    g_EventManager.Subscribe(Events::eTestEvent, [this](){ Player::OnTestEvent(); });

}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::Update(const float deltaTime)
{
    // Update Player Movement
    m_PlayerMovement.Update(deltaTime);

    // Update Player Rotation
    SetMouseRotation();

    // Update Player Assets
    m_PlayerSprite->Update(deltaTime, m_PlayerRectangle);

    // Play test Sound FX if F3 is Pressed
    if (CoreManagers::g_InputManager.GetActionPressed(CoreManagers::InputMappings::eDebug3))
    {
        CoreManagers::g_SoundManager.PlaySoundByID("snd_TestFX");
    }

    // Trigger Test Event if F4 is Pressed
    if (CoreManagers::g_InputManager.GetActionPressed(CoreManagers::InputMappings::eDebug4))
    {
        g_EventManager.Broadcast(Events::eTestEvent);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::Draw(SDL_Renderer* renderer)
{
    m_PlayerSprite->Draw(renderer);

    if (g_GameGlobals.m_bGraphicsDebugMode)
    {
        // Draw Debug Rectangle
        SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_BLACK.r, g_GameGlobals.COLOR_BLACK.g, g_GameGlobals.COLOR_BLACK.b, g_GameGlobals.COLOR_BLACK.a);
        SDL_RenderFillRect(renderer, &m_PlayerRectangle);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::SetPlayerPosition(int x, int y)
{
    m_PlayerRectangle.x = x;
    m_PlayerRectangle.y = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::OnTestEvent()
{
    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "TestEvent triggered from the Player class after pressing F4 button.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::SetMouseRotation()
{
    int iMouseX;
    int iMouseY;
    SDL_GetMouseState(&iMouseX, &iMouseY);

    double dNumberator = m_PlayerRectangle.x - iMouseX;
    double dDenominator = m_PlayerRectangle.y - iMouseY;
    double dRotation = atan2(dNumberator, dDenominator) * 180 / g_GameGlobals.PI;

    // Clockwise correction.
    dRotation *= -1;

    m_PlayerSprite->SetRotation(dRotation);
}

}