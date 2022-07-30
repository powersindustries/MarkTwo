#pragma once
#include <stdint.h>

#include "Core/Types/String.h"

namespace CoreSystems
{


// -------------------------------------------------------
// DISCLAIMER: These hashing methods are note safe! Do not use the hashing methods in this class for any security uses.
// These hashes are not safe, but they arent meant to be. Theyre used for fast lookups.
// -------------------------------------------------------
class HashMethods
{
public:
    HashMethods();
    ~HashMethods();

    uint32_t StringToHash32(CoreTypes::String& string);
    uint32_t StringToHash32(const char* string, const uint32_t size);


private:

    const uint32_t m_uiPrime1 = 37;
    const uint32_t m_uiPrime2 = 1993;

};

extern HashMethods g_HashMethods;

}