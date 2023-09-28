#ifndef Hash_h
#define Hash_h

#include <stdint.h>
#include <string>

#define PRIME_1 37

namespace Core
{
// -------------------------------------------------------
// DISCLAIMER: These hashing methods are note safe! Do not use the hashing methods in this class for any security uses.
// These hashes are not safe, but they arent meant to be. Theyre used for fast lookups.
// -------------------------------------------------------


// -------------------------------------------------------
// -------------------------------------------------------
static uint32_t StringToHash32(std::string string)
{
    uint32_t output = 0;
    const uint32_t stringSize = static_cast<uint32_t>(string.size());

    for (uint32_t x = 0; x < stringSize; ++x)
    {
        output = (output * PRIME_1) + string[x];
    }
    return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
static uint32_t StringToHash32(const char* string, const uint32_t size)
{
    uint32_t output = 0;

    for (uint32_t x=0; x<size; ++x) 
    {
        output = (output * PRIME_1) + string[x];
    }
    return output;
}

}

#endif