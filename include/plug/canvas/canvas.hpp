#ifndef PLUG_CANVAS_CANVAS_HPP
#define PLUG_CANVAS_CANVAS_HPP

#include "plug/canvas/selection_mask.hpp"
#include "plug/color.hpp"
#include "plug/graphics.hpp"
#include "plug/math/vec2d.hpp"

namespace plug 
{
    class Canvas 
    {
    public:
        Canvas() {}

        virtual ~Canvas(){};

        virtual void draw(const VertexArray &vertex_array) = 0;

        virtual void draw(const VertexArray &vertex_array, const Texture &texture) = 0;
        
        virtual Vec2d getSize(void) const = 0;
        virtual void setSize(const Vec2d &size) = 0;

        virtual SelectionMask &getSelectionMask(void) = 0;

        virtual Color getPixel(size_t x, size_t y) const = 0;
        virtual void setPixel(size_t x, size_t y, const Color &color) = 0;

        virtual const Texture &getTexture(void) const = 0;
    };
} // namespace plug

#endif  // PLUG_CANVAS_CANVAS_HPP

