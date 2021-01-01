#include "Collision.h"


namespace MarkTwo
{
    namespace GameCore
    {
        // ---------------------------------------------------------------------
        // AABB Collision type
        // https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
        // ---------------------------------------------------------------------
        bool Collision::CheckRectangleCollision(const SDL_Rect& rectangleA, SDL_Rect& rectangleB)
        {
            return (
                rectangleA.x + rectangleA.w >= rectangleB.x &&
                rectangleB.x + rectangleB.w >= rectangleA.x &&
                rectangleA.y + rectangleA.h >= rectangleB.y &&
                rectangleB.y + rectangleB.h >= rectangleA.y
                );
        }

    }
}
