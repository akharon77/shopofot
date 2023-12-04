#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include "plug/event.hpp"

enum PersonalEvents // : EventType
{
    Resize = 0
}

operator plug::EventType(PersonalEvents event);

#endif  // EVENT_EVENT_HPP

