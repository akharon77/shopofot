#ifndef PLUG_TOOL_TOOL_HPP
#define PLUG_TOOL_TOOL_HPP

#include "plug/canvas.hpp"
#include "plug/color.hpp"
#include "plug/plugin.hpp"
#include "plug/tool/color_palette.hpp"
#include "plug/tool/control_state.hpp"
#include "plug/widget.hpp"

namespace plug
{
    class Tool : public Plugin
    {
        public:
            virtual void setColorPalette(ColorPalette &palette) = 0;

            virtual void setActiveCanvas(Canvas &) = 0;

            virtual void onMainButton(const ControlState &state, const Vec2d &) = 0;
            virtual void onSecondaryButton(const ControlState &state,
                    const Vec2d &position) = 0;

            virtual void onModifier1(const ControlState &) = 0;
            virtual void onModifier2(const ControlState &) = 0;
            virtual void onModifier3(const ControlState &) = 0;

            virtual void onMove(const Vec2d &position) = 0;

            virtual void onConfirm(void) = 0;
            virtual void onCancel(void) = 0;

            virtual Widget *getWidget() = 0;

            virtual ~Tool() override = default;
    };
} // namespace plug

#endif  // PLUG_TOOL_TOOL_HPP

