#pragma once
#include <SDL.h>

namespace MarkTwo
{
    // Window values
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;

    // Runtime Values
    const unsigned int FPS = 60;
    const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

    // Collision type
    enum CollisionType
    {
        NO_COLLISION,
        PLAYER_ENEMY_COLLISION,
        PLAYER_PROJECTILE_COLLISION,
        ENEMY_PROJECTILE_COLLISION,
        PLAYER_VEGETATION_COLLIDER,
        PLAYER_LEVEL_COMPLETE_COLLISION,
        PLAYERPROJECTILE_ENEMY_COLLISION,
        PLAYERPROJECTILE_VEGETATION_COLLISION

    };

    // Rendering Layers
    enum LayerType
    {
        eTILEMAP_LAYER = 0,
        eVEGETATION_LAYER = 1,
        eENEMY_LAYER = 2,
        eOBSTACLE_LAYER = 3,
        ePLAYER_LAYER = 4,
        ePROJECTILE_LAYER = 5,
        eUI_LAYER = 6
    };

    const unsigned int NUM_LAYERS = 7;

    // Colors
    const SDL_Color WHITE_COLOR = { 255, 255, 255, 255 };
    const SDL_Color GREEN_COLOR = { 0, 255, 0, 255 };

    // Math constants
    const float PI_VALUE = 3.141592653589793238f;

}
