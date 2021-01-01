#pragma once
#include <string>
#include "../Constants.h"

namespace MarkTwo
{
    namespace Utilities
    {
        struct Math
        {
            float DegreesToRadians(float degrees);
            float Sine(float angleInRad);
            float Cosine(float angleInRad);
            float Tangent(float angleInRad);

            bool StringToBool(std::string stringVal);
        };
   
        extern Math g_Math;
    }
}
