#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include "Transform.h"
#include <map>

namespace MarkTwo
{


class AnimationData
{
public:
    AnimationData() : m_uiIndex(0), m_uiFrameCount(0), m_uiAnimationSpeed(0) {};
    ~AnimationData() {};

    AnimationData(unsigned int index, unsigned int frameCount, unsigned int animationSpeed)
    {
        m_uiIndex = index;
        m_uiFrameCount = frameCount;
        m_uiAnimationSpeed = animationSpeed;
    }

    unsigned int m_uiIndex;
    unsigned int m_uiFrameCount;
    unsigned int m_uiAnimationSpeed;
};


class Sprite
{
public:
    Sprite();
    ~Sprite();

    Sprite(std::string assetID);
    Sprite(std::string assetID, int numFrames, int animationSpeed, bool hasDirection);

    void InitializeSprite(SDL_Rect& inRectangle);
    void InitializeSprite(int x, int y, int width, int height);

    void Update(float deltaTime);
    void Update(float deltaTime, SDL_Rect& inRectangle);
    void Update(float deltaTime, Transform& inTransform);
    void Draw(SDL_Renderer* renderer);

    void Play(std::string animationName);

    void SetTexture(std::string textureID);


public:
    Transform m_Transform;


private:
    SDL_Texture* m_Texture;
    SDL_Rect m_SourceRectangle;
    SDL_Rect m_DestinationRectangle;


    std::map<std::string, AnimationData> m_Animations;
    std::string m_sCurrentAnimationName;

    bool m_bIsAnimated;

    int m_iFrameNumber;
    int m_iAnimationSpeed;

    unsigned int m_uiAnimationIndex = 0;

};


}