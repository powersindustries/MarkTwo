#pragma once
#include <Windows.h>

#include "../Types/String.h"


namespace Systems
{


enum class LoggingLevel
{
    eInfo,
    eWarning,
    eError
};


// -------------------------------------------------------
// -------------------------------------------------------
static void SYSTEMS_LOG(const LoggingLevel level, const CoreTypes::String& message)
{
    CoreTypes::String sOutputMessage;
    switch (level)
    {
    case LoggingLevel::eInfo:
    {
        sOutputMessage.append("INFO: ");
        break;
    }
    case LoggingLevel::eWarning:
    {
        sOutputMessage.append("WARNING: ");
        break;
    }
    case LoggingLevel::eError:
    {
        sOutputMessage.append("ERROR: ");
        break;
    }
    default:
    {
        // Default to info if LoggingLevel doesnt exist.
        sOutputMessage.append("INFO: ");
        break;
    }
    }

    sOutputMessage.append(message);
    sOutputMessage.push_back('\n');

    OutputDebugString(sOutputMessage.c_str());
}


// -------------------------------------------------------
// -------------------------------------------------------
static void SYSTEMS_LOG(const LoggingLevel level, const char* message)
{
    CoreTypes::String sOutputMessage;
    switch (level)
    {
    case LoggingLevel::eInfo:
    {
        sOutputMessage.append("INFO: ");
        break;
    }
    case LoggingLevel::eWarning:
    {
        sOutputMessage.append("WARNING: ");
        break;
    }
    case LoggingLevel::eError:
    {
        sOutputMessage.append("ERROR: ");
        break;
    }
    default:
    {
        // Default to info if LoggingLevel doesnt exist.
        sOutputMessage.append("INFO: ");
        break;
    }
    }

    sOutputMessage.append(message);
    sOutputMessage.push_back('\n');

    OutputDebugString(sOutputMessage.c_str());
}

}