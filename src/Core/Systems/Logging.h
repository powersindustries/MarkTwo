#pragma once
#include <string>
#include <iostream>

namespace Core
{


enum class LoggingLevel
{
    eInfo,
    eWarning,
    eError,
    eTemp
};


// -------------------------------------------------------
// -------------------------------------------------------
static void SYSTEMS_LOG(const LoggingLevel level, const std::string message)
{
    std::string sOutputMessage;
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
    case LoggingLevel::eTemp:
    {
        sOutputMessage.append("TEMP: ");
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

    std::clog << sOutputMessage << std::endl;
}

}
