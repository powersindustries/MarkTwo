#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "PlayerMovement.h"
#include "Core/Types/Sprite.h"

using namespace Core;

namespace MarkTwo
{


class Player
{
public:
    Player();
    ~Player();

    void Initialize();

    void Update(const float deltaTime);
    void Draw(SDL_Renderer* renderer);

    SDL_Rect GetPlayerRectangle() { return m_PlayerRectangle; }
    void SetPlayerRectangle(SDL_Rect rectangle) { m_PlayerRectangle = rectangle; }

    void SetPlayerPosition(int x, int y);
    void SetPlayerPositionX(int x) { m_PlayerRectangle.x = x; };
    void SetPlayerPositionY(int y) { m_PlayerRectangle.y = y; };

    void OnTestEvent();

private:
    void SetMouseRotation();



private:
    SDL_Rect m_PlayerRectangle;

    Sprite* m_PlayerSprite;

    PlayerMovement m_PlayerMovement;


};

extern Player g_Player;


}