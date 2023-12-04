#include "event.hpp"

operator EventType(PersonalEvents event)
{
    return static_cast<EventType>(event + EventType::EventsCount);
}

