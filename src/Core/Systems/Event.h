#ifndef Event_h
#define Event_h

#include <vector>
#include <functional>

namespace Core
{

class Event
{
public:

    void SetEvent(std::function<void()>& inDelegate)
    {
        m_InFunction = inDelegate;
    }

    void OnBroadCast()
    {
        m_InFunction();
    }


private:

    std::function<void()> m_InFunction;

};

}

#endif