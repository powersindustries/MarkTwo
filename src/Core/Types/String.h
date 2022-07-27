#pragma once
#include <stdint.h>

namespace CoreTypes
{

class String
{
public:
    String();
    ~String();

    String(char* string);
    String(const String& string);

    char* c_str() const { return m_String; };
    uint32_t size() const { return m_uiStringLength; };

    void push_back(char character);

    void append(const String& string);
    void append(const char* string);

    String& operator=(const String& right);
    String& operator=(const char* right);

    bool operator<(const String& right) const;
    bool operator<(const char* right) const;
    
    bool operator>(const String& right) const;
    bool operator>(const char* right) const;


private:

    char* m_String;
    uint32_t m_uiStringLength;

};

}