#ifndef LAYOUT_BOX_HPP
#define LAYOUT_BOX_HPP

#include "math.hpp"

class LayoutBox
{
    public:
        virtual void onParentUpdate (const LayoutBox& parent_box) = 0;

        virtual Vec2d getSize     (void) const = 0;
        virtual Vec2d getPosition (void) const = 0;

        virtual bool setSize     (const Vec2d& size)     = 0;
        virtual bool setPosition (const Vec2d& position) = 0;

        virtual LayoutBox* clone (void) const = 0;

        virtual ~LayoutBox() = default;
};

#endif  // LAYOUT_BOX_HPP
