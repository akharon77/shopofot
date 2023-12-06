#ifndef PLUG_FILTER_HPP
#define PLUG_FILTER_HPP

#include "plug/canvas.hpp"
#include "plug/plugin.hpp"
#include "plug/widget.hpp"

namespace plug
{
    class Filter : public Plugin
    {
        public:
            virtual void applyFilter(Canvas &canvas) const = 0;

            virtual Widget *getWidget(void) = 0;

            virtual ~Filter() override = default;
    };
} // namespace plug

#endif  // PLUG_FILTER_HPP

