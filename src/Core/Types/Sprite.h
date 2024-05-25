#ifndef Sprite_h
#define Sprite_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <map>

#include "Transform.h"

namespace Core
{

class Sprite
{
public:

    Sprite();
    ~Sprite();

    Sprite(const uint8_t assetIdHash);
    Sprite(const uint8_t assetIdHash, const uint8_t animationSpeed);

    void Update(const float deltaTime);
    void Update(const float deltaTime, SDL_Rect& rectangle);
    void Draw(SDL_Renderer* renderer, const SDL_RendererFlip& flip = SDL_FLIP_NONE);

    void SetTexture(const uint32_t textureIdHash);

    void SetRotation(const double degrees);


private:

    SDL_Texture* m_Texture{};

    SDL_Rect m_SourceRectangle{};
    SDL_Rect m_DestinationRectangle{};

    Transform m_Transform;

    uint8_t m_uiFrameNumber{};
    uint8_t m_uiAnimationSpeed;

    // In Degrees, Clockwise
    double m_dRotation;

};

}

#endif