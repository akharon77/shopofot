#include "event/event.hpp"

operator plug::EventType(PersonalEvents event)
{
    return static_cast<plug::EventType>(event + plug::EventType::EventsCount);
}

