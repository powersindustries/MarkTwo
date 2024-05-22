#ifndef Player_h
#define Player_h

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

    void Initialize();

    void Update(const float deltaTime);
    void Draw(SDL_Renderer* renderer);

    SDL_Rect GetPlayerRectangle() const { return m_PlayerRectangle; }
    void SetPlayerRectangle(const SDL_Rect& rectangle) { m_PlayerRectangle = rectangle; }

    void SetPlayerPosition(const int x, const int y);
    void SetPlayerPositionX(const int x) { m_PlayerRectangle.x = x; };
    void SetPlayerPositionY(const int y) { m_PlayerRectangle.y = y; };

    void OnTestEvent();


private:

    void SetMouseRotation();


private:

    SDL_Rect m_PlayerRectangle{};
    Sprite* m_PlayerSprite;
    PlayerMovement m_PlayerMovement;

};

extern Player g_Player;

}

#endif