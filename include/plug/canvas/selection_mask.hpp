#ifndef PLUG_CANVAS_SELECTION_MASK_HPP
#define PLUG_CANVAS_SELECTION_MASK_HPP

#include <cstddef>

namespace plug
{
    class SelectionMask
    {
    public:
        virtual ~SelectionMask() {};

        virtual size_t getWidth(void) const = 0;
        virtual size_t getHeight(void) const = 0;

        virtual bool getPixel(size_t x, size_t y) const = 0;
        virtual void setPixel(size_t x, size_t y, bool value) = 0;

        virtual void fill(bool value) = 0;

        virtual void invert(void) = 0;
    };
} // namespace plug

#endif  // PLUG_CANVAS_SELECTION_MASK_HPP

