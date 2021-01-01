#pragma once
#include <SDL.h>


namespace MarkTwo
{
    namespace GameCore
    {
        class Collision
        {
        public:
            static bool CheckRectangleCollision(const SDL_Rect& rectangleA, SDL_Rect& rectangleB);

        };

    }
}
