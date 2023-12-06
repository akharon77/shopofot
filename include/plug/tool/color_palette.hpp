#ifndef PLUG_TOOL_COLOR_PALETTE_HPP
#define PLUG_TOOL_COLOR_PALETTE_HPP

#include "plug/color.hpp"

namespace plug
{
    class ColorPalette
    {
    public:
        virtual Color getFGColor(void) const = 0;
        virtual Color getBGColor(void) const = 0;

        virtual void setFGColor(Color new_fg_color) = 0;
        virtual void setBGColor(Color new_bg_color) = 0;

        virtual ~ColorPalette() {}
    };
} // namespace plug

#endif  // PLUG_TOOL_COLOR_PALETTE_HPP

