#ifndef PLUG_TOOL_CONTROL_STATE_HPP
#define PLUG_TOOL_CONTROL_STATE_HPP

namespace plug
{
    enum class State
    {
        Pressed,
        Released
    };

    struct ControlState
    {
        State state;
    };
} // namespace plug

#endif  // PLUG_TOOL_CONTROL_STATE_HPP

