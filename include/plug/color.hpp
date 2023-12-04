#ifndef PLUG_COLOR_HPP
#define PLUG_COLOR_HPP

#include <cstdint>

namespace plug
{
    class Color
    {
    public:
        Color(void) : Color(255, 255, 255, 255) {}

        Color(uint8_t red_, uint8_t green_, uint8_t blue_, uint8_t alpha_ = 255) :
            red(red_), green(green_), blue(blue_), alpha(alpha_) 
        {}

        union
        {
            uint8_t red;
            uint8_t r;
        };

        union
        {
            uint8_t green;
            uint8_t g;
        };

        union
        {
            uint8_t blue;
            uint8_t b;
        };

        union
        {
            uint8_t alpha;
            uint8_t a;
        };
    };
} // namespace plug

#endif  // PLUG_COLOR_HPP

