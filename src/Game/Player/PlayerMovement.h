#ifndef PlayerMovement_h
#define PlayerMovement_h

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

    void Update(const float deltaTime);

    bool GetPlayerMoving() const { return m_bPlayerMoving; }
    void SetPlayerMoving(const bool isMoving) { m_bPlayerMoving = isMoving; }

    Direction GetDirection() const { return m_Direction; }
    void SetPlayerMoving(const Direction& direction) { m_Direction = direction; }


private:

    Direction m_Direction;
    bool m_bPlayerMoving;
    int m_iPlayerSpeed = 2;

};
}

#endif