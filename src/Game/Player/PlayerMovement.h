#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "GameGlobals.h"

namespace MarkTwo
{
class PlayerMovement
{
public:
    PlayerMovement();
    ~PlayerMovement();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    bool GetPlayerMoving() { return m_bPlayerMoving; }
    void SetPlayerMoving(bool isMoving) { m_bPlayerMoving = isMoving; }

    Direction GetDirection() { return m_Direction; }
    void SetPlayerMoving(Direction direction) { m_Direction = direction; }


private:

    Direction m_Direction;

    bool m_bPlayerMoving;

    int m_iPlayerSpeed = 2;

};
}