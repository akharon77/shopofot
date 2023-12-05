#ifndef GRAPHICS_SHAPES_HPP
#define GRAPHICS_SHAPES_HPP

#include "graphics/color.hpp"
#include "graphics/render_target.hpp"
#include "math.hpp"

void drawLine(plug::RenderTarget &target, 
        const plug::Vec2d &begin, const plug::Vec2d &end,
        const plug::Color color);

void drawCircle(plug::RenderTarget &target, 
        const plug::Vec2d &pos, const double radius,
        const plug::Color color);

void drawRectangle(plug::RenderTarget &target, 
        const plug::Vec2d &left_up, const plug::Vec2d &right_down,
        const plug::Color color);

void writeText(plug::RenderTarget &target,
        const plug::Vec2d &pos, 
        const char *text, const double thickness,
        const plug::Color color);

#endif  // GRAPHICS_SHAPES_HPP

