#ifndef Game_h
#define Game_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

namespace MarkTwo
{
class Game
{
public:

    Game();
    ~Game();

    void InitializeSession();
    void EndSession();

    void ProcessInputs();

    void Update();
    void Draw();


public:

    SDL_Window* m_Window;

    static SDL_Renderer* m_Renderer;


private:

    int m_iTicksLastFrame;

};
}

#endif