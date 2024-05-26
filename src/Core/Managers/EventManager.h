#ifndef EventManager_h
#define EventManager_h

#include <vector>
#include <functional>
#include <unordered_map>


namespace Core
{

class Event
{
public:

    void SetEvent(std::function<void()>& delegate)
    {
        m_Delegate = delegate;
    }

    void OnBroadCast()
    {
        m_Delegate();
    }


private:

    std::function<void()> m_Delegate;

};


class EventManager
{
public:

    void Broadcast(const std::string& eventId);
    void Subscribe(const std::string& eventId, std::function<void()> delegate);


private:

   // Key: Event Id Hash, Value: vector of Event objects
   std::unordered_map<uint8_t, std::vector<Event>> m_EventsMap;

};

extern EventManager g_EventManager;


}

#endif