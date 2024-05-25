#ifndef UIScreenBase_h
#define UIScreenBase_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

namespace UI
{

class UIScreenBase
{
public:

    virtual void Initialize();

    virtual void Update() = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;

    virtual void OnShow() {};
    virtual void RemoveSelf() = 0;

    virtual void HotReloadUI() {};

private:

    void OnDebugUIHotReloadCalled();


public:

    std::string m_sScreenId;

};

}

#endif