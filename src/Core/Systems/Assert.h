#ifndef Assert_h
#define Assert_h

#include <assert.h>

#include "Logging.h"

namespace Core
{


// -------------------------------------------------------
// Expression should be true. If not, assert will be hit.
// -------------------------------------------------------
static void SYSTEMS_ASSERT(const bool expression)
{
    if (!expression)
    {
        SYSTEMS_LOG(LoggingLevel::eError, "False Expression hit. Check logs for details.");
    }

    assert(expression);
}

}

#endif