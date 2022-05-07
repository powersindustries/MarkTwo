#include "Player.h"
#include "GameGlobals.h"

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
    m_PlayerSprite = new Sprite("txt_Chopper", 2, 90, true);
    m_PlayerSprite->InitializeSprite(m_PlayerRectangle);

    m_PlayerSprite->m_Transform.m_iPositionX = m_PlayerRectangle.x;
    m_PlayerSprite->m_Transform.m_iPositionY = m_PlayerRectangle.y;
    m_PlayerSprite->m_Transform.m_iWidth = m_PlayerRectangle.w;
    m_PlayerSprite->m_Transform.m_iHeight = m_PlayerRectangle.h;

}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::Update(float* deltaTime)
{
    // Update Player Movement
    m_PlayerMovement.Update(deltaTime);

    // Update Player Assets
    m_PlayerSprite->Update(*deltaTime, m_PlayerRectangle);
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

}