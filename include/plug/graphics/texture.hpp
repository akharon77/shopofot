#ifndef PLUG_GRAPHICS_TEXTURE_HPP
#define PLUG_GRAPHICS_TEXTURE_HPP

#include <cassert>
#include <cstddef>

#include "plug/color.hpp"

namespace plug
{
    struct Texture
    {
        Texture(size_t a_width, size_t a_height) :
            data((Color*) new Color[a_width * a_height]),
            width(a_width),
            height(a_height)
        {}

        Texture(size_t a_width, size_t a_height, const Color *a_data) :
            Texture(a_width, a_height)
        {
            for (size_t i = 0; i < width * height; ++i)
                data[i] = a_data[i];
        }

        Texture(const Texture &other) :
            Texture(other.width, other.height, other.data)
        {}

        Texture& operator = (const Texture &other) = delete;

        ~Texture(void)
        {
            delete[] data;
        }

        plug::Color getPixel(size_t x, size_t y) const
        {
            assert(x < width);
            assert(y < height);
            return data[y * width + x];
        }

        void setPixel(size_t x, size_t y, plug::Color color) const
        {
            assert(x < width);
            assert(y < height);
            data[y * width + x] = color;
        }

        Color *const data;
        const size_t width;
        const size_t height;
    };

} // namespace plug

#endif  // PLUG_GRAPHICS_TEXTURE_HPP

