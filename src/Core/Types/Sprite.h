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

    Sprite(uint32_t assetIDHash);
    Sprite(uint32_t assetIDHash, uint8_t animationSpeed);

    void Update(const float deltaTime);
    void Update(const float deltaTime, SDL_Rect& inRectangle);
    void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void SetTexture(uint32_t textureIDHash);

    void SetRotation(double degrees);


private:
    SDL_Texture* m_Texture;

    SDL_Rect m_SourceRectangle;
    SDL_Rect m_DestinationRectangle;

    Transform m_Transform;

    uint8_t m_uiFrameNumber;
    uint8_t m_uiAnimationSpeed;

    // In Degrees, Clockwise
    double m_dRotation;

};

}

#endif