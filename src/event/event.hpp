#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include "plug/event.hpp"
#include "math.hpp"

enum PersonalEvents // : EventType
{
    Resize = 0
}

operator plug::EventType(PersonalEvents event);

struct ResizeEvent : public plug::Event
{
    ResizeEvent(const plug::Vec2d &new_size) :
        Event((plug::EventType) PersonalEvents::Resize)
        size(new_size)
    {}

    plug::Vec2d size;
};

#endif  // EVENT_EVENT_HPP

