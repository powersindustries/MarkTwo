#ifndef EventManager_h
#define EventManager_h

#include <vector>
#include <functional>
#include <unordered_map>
#include <stdint.h>

#include "Core/Systems/Event.h"


namespace MarkTwo
{

enum class Events
{
    eTestEvent,
    eCount
};

class EventManager
{
public:
    EventManager();
    ~EventManager();

    void Initialize();

    void Broadcast(Events eEvent);
    void Subscribe(Events eEvent, std::function<void()> inDelegate);


private:

    std::vector<std::vector<Core::Event>> m_EventsVector;
    std::unordered_map<Events, uint16_t> m_EventsMap; // Key: Events enum, Value: index in m_EventsVector

};

extern EventManager g_EventManager;


}

#endif