#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "event.hpp"
#include "plug/layoutbox.hpp"
#include "util/list.hpp"
#include "plug/math.hpp"
#include "plug/widget.hpp"

using Transform = plug::Transform;
using Vec2d     = plug::Vec2d;

class Container
{
    public:
        virtual bool close(int32_t id) = 0;
};

enum Corner
{
  TopLeft = 0,
  TopRight,
  BottomLeft,
  BottomRight,
};

class Widget : public plug::Widget
{
    plug::LayoutBox *m_layout_box;

public:
    explicit Widget(const plug::LayoutBox &box);

    Widget(const Widget &rhs);
    Widget& operator = (const Widget &rhs);

    ~Widget() override;

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual void onEvent(const plug::Event &event, plug::EHC &context) override;

    virtual void onParentUpdate(const plug::LayoutBox &parent_box) override;

    virtual       plug::LayoutBox &getLayoutBox()                     override;
    virtual const plug::LayoutBox &getLayoutBox() const               override;

    virtual void setLayoutBox(const plug::LayoutBox &box) override;

protected:
    virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const override;

    plug::Vec2d getCorner(Corner corner, const plug::TransformStack &stack) const;

    virtual void onTick             (const plug::TickEvent             &event, plug::EHC &context) override;
    virtual void onMouseMove        (const plug::MouseMoveEvent        &event, plug::EHC &context) override;
    virtual void onMousePressed     (const plug::MousePressedEvent     &event, plug::EHC &context) override;
    virtual void onMouseReleased    (const plug::MouseReleasedEvent    &event, plug::EHC &context) override;
    virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent  &event, plug::EHC &context) override;
    virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context) override;
    virtual void onResize           (const ResizeEvent                 &event, plug::EHC &context);

    virtual void onTime(double d_seconds, plug::EHC &context) {}

    virtual void onMouseMoved (double x, double y, plug::EHC &context) {}

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) {}
    virtual void onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) {}

    virtual void onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) {}
    virtual void onKeyboardReleased (plug::KeyCode key, plug::EHC &context) {}

    virtual void onResize(double width, double height, plug::EHC &context) {}
};

#endif  // WIDGET_HPP

