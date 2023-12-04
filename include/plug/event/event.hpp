#ifndef PLUG_EVENT_EVENT_HPP
#define PLUG_EVENT_EVENT_HPP

#include <cstddef>

#include "event/key_code.hpp"
#include "event/mouse_button.hpp"
#include "math.hpp"

namespace plug
{

    enum EventType
    {
        Tick              = 0,
        MouseMove         = 1,
        MousePressed      = 2,
        MouseReleased     = 3,
        KeyboardPressed   = 4,
        KeyboardReleased  = 5
    };

    class Event
    {
        public:
            Event(size_t type) : m_type(type) {}

            size_t getType(void) const { return m_type; }

        private:
            const size_t m_type;
    };

    struct MouseMoveEvent : public Event
    {
        MouseMoveEvent(const Vec2d &position,
                bool shift_pressed, bool ctrl_pressed, bool alt_pressed) :
            Event(MouseMove),
            shift(shift_pressed), ctrl(ctrl_pressed), alt(alt_pressed),
            pos(position)
        {}

        bool  shift;
        bool  ctrl;
        bool  alt;
        Vec2d pos;
    };

    struct MousePressedEvent : public Event
    {
        MousePressedEvent(MouseButton button, const Vec2d &position,
                          bool shift_pressed, bool ctrl_pressed, bool alt_pressed) :
            Event(MousePressed),
            button_id(button), 
            shift(shift_pressed), ctrl(ctrl_pressed), alt(alt_pressed), pos(position)
        {}

        MouseButton button_id;
        bool        shift;
        bool        ctrl;
        bool        alt;
        Vec2d       pos;
    };

    struct MouseReleasedEvent : public Event
    {
        MouseReleasedEvent(MouseButton button,
                           const Vec2d &position,
                           bool shift_pressed, bool ctrl_pressed, bool alt_pressed) :
            Event(MouseReleased),
            button_id(button), 
            shift(shift_pressed), ctrl(ctrl_pressed), alt(alt_pressed),
            pos(position)
        {}

        MouseButton button_id;
        bool        shift;
        bool        ctrl;
        bool        alt;
        Vec2d       pos;
    };

    struct KeyboardPressedEvent : public Event
    {
        KeyboardPressedEvent(KeyCode key,
                             bool shift_pressed,
                             bool ctrl_pressed,
                             bool alt_pressed) :
            Event(KeyboardPressed),
            key_id(key),
            shift(shift_pressed),
            ctrl(ctrl_pressed),
            alt(alt_pressed)
        {}

        KeyCode key_id;
        bool    shift;
        bool    ctrl;
        bool    alt;
    };

    struct KeyboardReleasedEvent : public Event
    {
        KeyboardReleasedEvent(KeyCode key, 
                              bool shift_pressed,
                              bool ctrl_pressed,
                              bool alt_pressed) :
            Event(KeyboardReleased),
            key_id(key),
            shift(shift_pressed),
            ctrl(ctrl_pressed),
            alt(alt_pressed)
        {}

        KeyCode key_id;
        bool    shift;
        bool    ctrl;
        bool    alt;
    };

    struct TickEvent : public Event
    {
        TickEvent(double seconds) : Event(Tick), delta_time(seconds) {}

        double delta_time;
    };

} // namespace plug

#endif  // PLUG_EVENT_EVENT_HPP

