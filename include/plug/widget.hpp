#ifndef PLUG_WIDGET_HPP
#define PLUG_WIDGET_HPP

#include "plug/event.hpp"
#include "plug/graphics.hpp"
#include "plug/layout_box.hpp"
#include "plug/math.hpp"

namespace plug
{
    class Widget
    {
    public:
        virtual ~Widget() {}

        virtual void draw(TransformStack &stack, RenderTarget &target) = 0;

        virtual void onEvent(const Event &event, EHC &context) = 0;

        virtual void onParentUpdate(const LayoutBox &parent_box) = 0;

        virtual       LayoutBox &getLayoutBox()                     = 0;
        virtual const LayoutBox &getLayoutBox() const               = 0;
        virtual       void       setLayoutBox(const LayoutBox &box) = 0;

    protected:
        virtual bool covers(TransformStack &stack, const Vec2d &position) const = 0;

        virtual void onTick             (const TickEvent             &event, EHC &context) {}
        virtual void onMouseMove        (const MouseMoveEvent        &event, EHC &context) {}
        virtual void onMousePressed     (const MousePressedEvent     &event, EHC &context) {}
        virtual void onMouseReleased    (const MouseReleasedEvent    &event, EHC &context) {}
        virtual void onKeyboardPressed  (const KeyboardPressedEvent  &event, EHC &context) {}
        virtual void onKeyboardReleased (const KeyboardReleasedEvent &event, EHC &context) {}
    };

} // namespace plug

#endif  // PLUG_WIDGET_HPP

