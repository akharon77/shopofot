#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "event.hpp"
#include "list.hpp"
#include "math.hpp"
#include "plug/widget.hpp"
#include "ui/layout_box.hpp"

class Container
{
    public:
        virtual bool close(int32_t id) = 0;
};

class Widget : public plug::Widget
{
    LayoutBox *m_layout_box;

public:
    explicit Widget(const LayoutBox &box);

    Widget(const Widget &rhs) = delete;
    Widget& operator = (const Widget &rhs) = delete;

    ~Widget() override;

    virtual void draw(TransformStack &stack, RenderTarget &target) override;

    virtual void onEvent(const Event &event, EHC &context) override;

    virtual void onParentUpdate(const LayoutBox &parent_box) override;

    virtual       LayoutBox &getLayoutBox()                     override;
    virtual const LayoutBox &getLayoutBox() const               override;
    virtual       void       setLayoutBox(const LayoutBox &box) override;

    virtual bool onTime (double d_seconds) {};

    virtual bool onMouseMoved (double x, double y, EHC &context) {};

    virtual bool onMousePressed  (MouseButton key, double x, double y, EHC &context) {};
    virtual bool onMouseReleased (MouseButton key, double x, double y, EHC &context) {};

    virtual bool onKeyboardPressed  (KeyCode key) {};
    virtual bool onKeyboardReleased (KeyCode key) {};

    virtual bool onResize(double width, double height) {};

protected:
    virtual bool covers(TransformStack &stack, const Vec2d &position) const override;

    virtual void onTick             (const TickEvent             &event, EHC &context) override;
    virtual void onMouseMove        (const MouseMoveEvent        &event, EHC &context) override;
    virtual void onMousePressed     (const MousePressedEvent     &event, EHC &context) override;
    virtual void onMouseReleased    (const MouseReleasedEvent    &event, EHC &context) override;
    virtual void onKeyboardPressed  (const KeyboardPressedEvent  &event, EHC &context) override;
    virtual void onKeyboardReleased (const KeyboardReleasedEvent &event, EHC &context) override;
};

void adaptSfEvent(sf::Event event, Widget &widget, List<Transform> &transf_list);

#endif  // WIDGET_HPP

