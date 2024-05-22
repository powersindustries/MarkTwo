#ifndef Icon_h
#define Icon_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "Core/UI/Types/UIBase.h"


namespace UI
{
class Icon : public UIBase
{
public:

    Icon();

    void Draw(SDL_Renderer* renderer) override;
    void SetTexture(const uint32_t uiTextureId);


private:

    SDL_Texture* m_Texture;

};
}

#endif