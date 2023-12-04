#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "event.hpp"
#include "layoutbox.hpp"
#include "util/list.hpp"
#include "math.hpp"
#include "plug/widget.hpp"

class Container
{
    public:
        virtual bool close(int32_t id) = 0;
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

    virtual bool onTime (double d_seconds) {};

    virtual bool onMouseMoved (double x, double y, plug::EHC &context) {};

    virtual bool onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) {};
    virtual bool onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) {};

    virtual bool onKeyboardPressed  (plug::KeyCode key) {};
    virtual bool onKeyboardReleased (plug::KeyCode key) {};

    virtual bool onResize(double width, double height) {};

protected:
    virtual bool covers(plug::TransformStack &stack, const plug::Vec2d &position) const override;

    virtual void onTick             (const plug::TickEvent             &event, plug::EHC &context) override;
    virtual void onMouseMove        (const plug::MouseMoveEvent        &event, plug::EHC &context) override;
    virtual void onMousePressed     (const plug::MousePressedEvent     &event, plug::EHC &context) override;
    virtual void onMouseReleased    (const plug::MouseReleasedEvent    &event, plug::EHC &context) override;
    virtual void onKeyboardPressed  (const plug::KeyboardPressedEvent  &event, plug::EHC &context) override;
    virtual void onKeyboardReleased (const plug::KeyboardReleasedEvent &event, plug::EHC &context) override;
};

#endif  // WIDGET_HPP

