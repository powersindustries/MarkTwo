#ifndef Transform_h
#define Transform_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

namespace Core
{

class Transform
{
public:

    Transform();

    void SetTransform(const SDL_Rect& rectangle, int s = 1);
    void SetTransform(const int x, const int y, const int w, const int h, int s = 1);

    void SetPosition(const int x, const int y);
    void SetPosition(const SDL_Rect& rectangle);


public:

    int m_iPositionX;
    int m_iPositionY;

    int m_iWidth;
    int m_iHeight;
    int m_iScale;

};

}

#endif