#ifndef PLUG_LAYOUT_BOX_HPP
#define PLUG_LAYOUT_BOX_HPP

#include "plug/math.hpp"

namespace plug
{
    class LayoutBox
    {
    public:
        virtual void onParentUpdate(const LayoutBox &parent_box) = 0;

        virtual Vec2d getSize     (void) const = 0;
        virtual Vec2d getPosition (void) const = 0;

        virtual bool setSize     (const Vec2d &size)     = 0;
        virtual bool setPosition (const Vec2d &position) = 0;

        virtual LayoutBox *clone(void) const = 0;
        virtual ~LayoutBox() {}
    };
} // namespace plug

#endif  // PLUG_LAYOUT_BOX_HPP

