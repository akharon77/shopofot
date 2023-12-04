#ifndef EVENT_HPP
#define EVENT_HPP

#include "plug/event.hpp"

using EventType             = plug::EventType;
using Event                 = plug::Event;
using MouseMoveEvent        = plug::MouseMoveEvent;
using MousePressedEvent     = plug::MousePressedEvent;
using MouseReleasedEvent    = plug::MouseReleasedEvent;
using KeyboardPressedEvent  = plug::KeyboardPressedEvent;
using KeyboardReleasedEvent = plug::KeyboardReleasedEvent;
using TickEvent             = plug::TickEvent;

enum PersonalEvents // : EventType
{
    Resize = 0
}

operator EventType(PersonalEvents event);

#endif  // EVENT_HPP

