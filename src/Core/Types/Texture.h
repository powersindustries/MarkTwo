#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <map>

#include "Transform.h"

namespace Core
{

class Texture
{
public:
	Texture();
	~Texture();

	Texture(uint32_t uiAssetID);
	
	void Draw(SDL_Renderer* renderer);

	void SetTexture(const uint32_t uiTextureID);

	void SetSize(int w, int h);
	void SetPosition(int x, int y);


private:

	SDL_Texture* m_Texture;

	SDL_Rect m_BaseRectangle;
	SDL_Color m_Color;

};

}