#include "String.h"
#include <cstring>

#define NULL_TERMINATE_CHAR '\0'

namespace CoreTypes
{


// -------------------------------------------------------
// -------------------------------------------------------
String::String()
    : m_String(nullptr), m_uiStringLength(0)
{
    m_String = new char[1];
    m_String[0] = NULL_TERMINATE_CHAR;
}

// -------------------------------------------------------
// -------------------------------------------------------
String::~String()
{
    delete m_String;
}


// -------------------------------------------------------
// -------------------------------------------------------
String::String(char* string)
    : m_String(nullptr), m_uiStringLength(0)
{
    if (!string)
    {
        m_String = new char[1];
        m_String[0] = NULL_TERMINATE_CHAR;
        return;
    }

    m_uiStringLength = static_cast<uint32_t>(strlen(string));

    m_String = new char[m_uiStringLength + 1];

    strcpy(m_String, string);
    m_String[m_uiStringLength] = NULL_TERMINATE_CHAR;
}


// -------------------------------------------------------
// -------------------------------------------------------
String::String(const String& string)
    : m_String(nullptr), m_uiStringLength(0)
{
    m_uiStringLength = static_cast<uint32_t>(strlen(string.c_str()));

    m_String = new char[m_uiStringLength + 1];
    strcpy(m_String, string.c_str());

    m_String[m_uiStringLength] = NULL_TERMINATE_CHAR;
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::push_back(char character)
{
    const uint8_t sizeIncrease = 2;
    char* tempString = new char[m_uiStringLength + sizeIncrease];

    for (uint32_t x = 0; x < m_uiStringLength; ++x)
    {
        tempString[x] = m_String[x];
    }

    tempString[m_uiStringLength] = character;
    tempString[m_uiStringLength + 1] = NULL_TERMINATE_CHAR;

    delete[] m_String;

    m_String = tempString;
    m_uiStringLength++;
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::append(const String& string)
{
    const uint8_t sizeIncrease = 1;

    const uint32_t inputStringSize = string.size();
    const uint32_t finalStringSize = m_uiStringLength + inputStringSize;

    char* tempString = new char[finalStringSize + sizeIncrease];

    for (uint32_t x = 0; x < m_uiStringLength; ++x)
    {
        tempString[x] = m_String[x];
    }

    for (uint32_t x = m_uiStringLength; x < finalStringSize; ++x)
    {
        tempString[x] = string.c_str()[x - m_uiStringLength]; // fix later
    }

    tempString[finalStringSize] = NULL_TERMINATE_CHAR;

    delete[] m_String;
    m_String = tempString;
    m_uiStringLength = finalStringSize;
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::append(const char* string)
{
    const uint8_t sizeIncrease = 1;

    const uint32_t inputStringSize = static_cast<uint32_t>(strlen(string));
    const uint32_t finalStringSize = m_uiStringLength + inputStringSize;

    char* tempString = new char[finalStringSize + sizeIncrease];

    for (uint32_t x = 0; x < m_uiStringLength; ++x)
    {
        tempString[x] = m_String[x];
    }

    for (uint32_t x = m_uiStringLength; x < finalStringSize; ++x)
    {
        tempString[x] = string[x - m_uiStringLength];
    }

    tempString[finalStringSize] = NULL_TERMINATE_CHAR;

    delete[] m_String;
    m_String = tempString;
    m_uiStringLength = finalStringSize;
}


// -------------------------------------------------------
// -------------------------------------------------------
String& String::operator=(const String& right)
{
    if (this == &right)
    {
        return *this;
    }

    m_uiStringLength = static_cast<uint32_t>(strlen(right.c_str())) ;

    delete[] m_String;
    m_String = new char[m_uiStringLength + 1];
    strcpy(m_String, right.c_str());

    return *this;
}


// -------------------------------------------------------
// -------------------------------------------------------
String& String::operator=(const char* right)
{
    if (this->m_String == right)
    {
        return *this;
    }

    m_uiStringLength = static_cast<uint32_t>(strlen(right));

    delete[] m_String;
    m_String = new char[m_uiStringLength + 1];
    strcpy(m_String, right);

    return *this;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator<(const String& right) const
{
    return strcmp(this->m_String, right.c_str()) > 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator<(const char* right) const
{
    return strcmp(this->m_String, right) > 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator>(const String& right) const
{
    return strcmp(this->m_String, right.c_str()) < 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator>(const char* right) const
{
    return strcmp(this->m_String, right) < 0;

}

}
