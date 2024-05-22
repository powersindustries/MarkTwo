#include "Player.h"
#include <cmath>

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
    m_PlayerRectangle.y = 150;
    m_PlayerRectangle.w = 32;
    m_PlayerRectangle.h = 32;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::Initialize()
{
    // Initialize Player Sprite
    m_PlayerSprite = new Sprite(Core::StringToHash32(std::string("txt_Chopper")), 90);

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
    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eDebug3))
    {
        Core::g_SoundManager.PlaySoundByID("snd_TestFX");
    }

    // Trigger Test Event if F4 is Pressed
    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eDebug4))
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
void Player::SetPlayerPosition(const int x, const int y)
{
    m_PlayerRectangle.x = x;
    m_PlayerRectangle.y = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::OnTestEvent()
{
    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "TestEvent triggered from the Player class after pressing F4 button.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::SetMouseRotation()
{
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    double numerator = m_PlayerRectangle.x - mouseX;
    double denominator = m_PlayerRectangle.y - mouseY;
    double rotation = atan2(numerator, denominator) * 180 / g_GameGlobals.PI;

    // Clockwise correction.
    rotation *= -1;

    m_PlayerSprite->SetRotation(rotation);
}

}