#include "Math.h"
#include <cmath>

namespace MarkTwo
{
    namespace Utilities
    {
        Math g_Math;


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        float Math::DegreesToRadians(float degrees)
        {
            return degrees * (PI_VALUE / 180);
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        bool Math::StringToBool(std::string stringVal)
        {
            return stringVal == "true" || stringVal == "True" || stringVal == "TRUE" || stringVal == "1" ? true : false;
        }
    }
}
