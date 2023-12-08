#ifndef COLOR_PALETTE_HPP
#define COLOR_PALETTE_HPP

#include "plug/tool/color_palette.hpp"

class ColorPalette : public plug::ColorPalette
{
public:
    ColorPalette() :
        m_bg_color(plug::Color(0, 0, 0)), m_fg_color(plug::Color(255, 255, 255))
    {}

    ~ColorPalette() {}

    virtual plug::Color getFGColor(void) const override;
    virtual plug::Color getBGColor(void) const override;

    virtual void setFGColor(plug::Color new_fg_color) override;
    virtual void setBGColor(plug::Color new_bg_color) override;

    ColorPalette(const ColorPalette &other) = delete;
    ColorPalette &operator= (const ColorPalette &other) = delete;

private:
    plug::Color m_bg_color;
    plug::Color m_fg_color;
};

#endif  // COLOR_PALETTE_HPP

