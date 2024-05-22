#ifndef Utility_h
#define Utility_h

#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>
#include "GameGlobals.h"
#include "VectorMethods.h"

namespace Core
{

class Utility
{
public:

	static double DistanceBetweenTwoPoints(const int rect1X, const int rect1Y, const int rect2X, const int rect2Y);
	static double DirectionalDistanceBetweenTwoRectangles(const MarkTwo::Direction& direction, const SDL_Rect& rect1, const SDL_Rect& rect2);

	static bool CollisionBetweenTwoRectangles(const SDL_Rect& rect1, const SDL_Rect& rect2);
	static bool CollisionBetweenTwoRectanglesWithPadding(const SDL_Rect& rect1, const SDL_Rect& rect2, const int padding);
	static bool CollisionBetweenPointAndRectangle(const SDL_Rect& rect, const Core::Vec2i& v2i);

	static double ATan2InDegrees(const int x, const int y);
	static double ATan2InRadians(const int x, const int y);

	static bool StringToBool(const std::string& text);

};

}

#endif