#include "EventManager.h"
#include "Core/Systems/Assert.h"

namespace MarkTwo
{


// -------------------------------------------------------
// -------------------------------------------------------
EventManager g_EventManager;


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::Initialize()
{
    const uint16_t eventsCount = static_cast<uint16_t>(Events::eCount);
    m_EventsVector.reserve(eventsCount);

    for (uint16_t x = 0; x < eventsCount; ++x)
    {
        std::vector<Core::Event> newEvent;
        m_EventsVector.push_back(newEvent);

        m_EventsMap.insert({ static_cast<Events>(x), x });
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::Broadcast(const Events& event)
{
    Core::SYSTEMS_ASSERT(m_EventsMap.find(event) != m_EventsMap.end());

    const uint16_t eventIndex = m_EventsMap[event];
    std::vector<Core::Event> eventsVector = m_EventsVector[eventIndex];

    const uint16_t eventsCount = static_cast<uint16_t>(eventsVector.size());
    for (uint16_t x = 0; x < eventsCount; ++x)
    {
        eventsVector[x].OnBroadCast();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::Subscribe(const Events& event, std::function<void()> inDelegate)
{
    Core::SYSTEMS_ASSERT(m_EventsMap.find(event) != m_EventsMap.end());

    std::vector<Core::Event>& eventsVector = m_EventsVector[m_EventsMap[event]];

    Core::Event newSubscription;
    newSubscription.SetEvent(inDelegate);

    eventsVector.push_back(newSubscription);
}

}