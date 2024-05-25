#include "EventManager.h"
#include "Core/Systems/Assert.h"
#include "Core/Systems/Hash.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
EventManager g_EventManager;


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::Broadcast(const std::string& eventId)
{
    const uint8_t hashedId = Core::StringToHash(eventId);
    if (m_EventsMap.find(hashedId) != m_EventsMap.end())
    {
        std::vector<Event>& eventsVector = m_EventsMap[hashedId];

        const uint32_t eventsCount = static_cast<uint32_t>(eventsVector.size());
        for (uint32_t x = 0; x < eventsCount; ++x)
        {
            eventsVector[x].OnBroadCast();
        }
    }
    else
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "EventId: " + eventId + " does not exist in events map.");
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::Subscribe(const std::string& eventId, std::function<void()> delegate)
{
    const uint8_t hashedId = Core::StringToHash(eventId);

    // Add new Event.
    if (m_EventsMap.find(hashedId) == m_EventsMap.end())
    {
        // Create new event.
        std::vector<Event> newEventVector;
        newEventVector.reserve(INT16_MAX);

        m_EventsMap.insert({hashedId, newEventVector});
    }

    // Add new subscription.
    std::vector<Event>& eventsVector = m_EventsMap[hashedId];

    Event newSubscription;
    newSubscription.SetEvent(delegate);

    eventsVector.push_back(newSubscription);
}

}