#include "Hash.h"

namespace CoreSystems
{


// -------------------------------------------------------
// -------------------------------------------------------
HashMethods g_HashMethods;


// -------------------------------------------------------
// -------------------------------------------------------
HashMethods::HashMethods()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
HashMethods::~HashMethods()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
uint32_t HashMethods::StringToHash32(CoreTypes::String& string)
{
    uint32_t output = 0;
    const uint32_t stringSize = string.size();

    for (uint32_t x=0; x<stringSize; ++x) 
    {
        output = (output * m_uiPrime1) + string[x];
    }
    return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
uint32_t HashMethods::StringToHash32(const char* string, const uint32_t size)
{
    uint32_t output = 0;

    for (uint32_t x=0; x<size; ++x) 
    {
        output = (output * m_uiPrime1) + string[x];
    }
    return output;
}

}