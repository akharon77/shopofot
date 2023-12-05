#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include "plug/event.hpp"
#include "math.hpp"

enum PersonalEvents // : EventType
{
    Resize = 10
};

struct ResizeEvent : public plug::Event
{
    ResizeEvent(const plug::Vec2d &new_size) :
        Event(PersonalEvents::Resize),
        size(new_size)
    {}

    plug::Vec2d size;
};

#endif  // EVENT_EVENT_HPP

