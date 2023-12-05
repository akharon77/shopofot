#include "plug/graphics/vertex_array.hpp"
#include "math/transform_stack.hpp"
#include "widget.hpp"

#include <cmath>

Widget::Widget(const Widget &widget) :
    m_layout_box(widget.getLayoutBox().clone()) 
{}

plug::LayoutBox& Widget::getLayoutBox()
{
    return *m_layout_box;
}

const plug::LayoutBox& Widget::getLayoutBox() const
{
    return *m_layout_box;
}

void Widget::setLayoutBox(const plug::LayoutBox &box)
{
    delete m_layout_box;
    m_layout_box = box.clone();
}

Widget& Widget::operator = (const Widget &widget)
{
    if (this == &widget)
        return *this;

    delete m_layout_box;
    m_layout_box = widget.m_layout_box->clone();
    return *this;
}

Widget::~Widget()
{
    delete m_layout_box;
}

void Widget::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    static plug::VertexArray vertices(plug::PrimitiveType::LinesStrip, 5);

    vertices[0].position = getCorner(Corner::TopLeft,     stack);
    vertices[1].position = getCorner(Corner::TopRight,    stack);
    vertices[2].position = getCorner(Corner::BottomRight, stack);
    vertices[3].position = getCorner(Corner::BottomLeft,  stack);

    vertices[4] = vertices[0];

    for (size_t id = 0; id < vertices.getSize(); ++id)
        vertices[id].color = plug::Color(255, 0, 255, 255);

    target.draw(vertices);
}

void Widget::onEvent(const plug::Event &event, plug::EHC &context)
{
    switch (event.getType())
    {
        case plug::EventType::Tick: 
            {
                onTick((const plug::TickEvent&) event, context);
            } 
            break;

        case plug::EventType::KeyboardPressed: 
            {
                onKeyboardPressed((const plug::KeyboardPressedEvent&) event, context);
            }
            break;

        case plug::EventType::KeyboardReleased: 
            {
                onKeyboardReleased((const plug::KeyboardReleasedEvent&) event, context);
            } 
            break;

        case plug::EventType::MousePressed: 
            {
                onMousePressed((const plug::MousePressedEvent&) event, context);
            }
            break;

        case plug::EventType::MouseReleased: 
            {
                onMouseReleased((const plug::MouseReleasedEvent&) event, context);
            }
            break;

        case plug::EventType::MouseMove:
            {
                onMouseMove((const plug::MouseMoveEvent&) event, context);
            }
            break;

        case (plug::EventType) PersonalEvents::Resize:
            {
                onResize((const ResizeEvent&) event, context);
            }
            break;

        default:
            break;
    }
}

void Widget::onParentUpdate(const plug::LayoutBox &parent_box)
{
    m_layout_box->onParentUpdate(parent_box);
}

plug::Vec2d Widget::getCorner(Corner corner, const plug::TransformStack &stack) const
{
    plug::Vec2d direction((corner & 1) ? 0.5 : -0.5, (corner & 2) ? -0.5 : 0.5);
    plug::Vec2d corner_pos = m_layout_box->getPosition() + m_layout_box->getSize() * direction;

    return stack.top().apply(corner_pos);
}

static inline bool isSmall(double a)
{
    return fabs(a) < 1e-6;
}

bool Widget::covers(plug::TransformStack &stack, const plug::Vec2d &position) const
{
    if (isSmall(m_layout_box->getSize().x) || isSmall(m_layout_box->getSize().y))
        return false;

    plug::Vec2d tl = getCorner(TopLeft,     stack);
    plug::Vec2d tr = getCorner(TopRight,    stack);
    plug::Vec2d br = getCorner(BottomRight, stack);
    plug::Vec2d bl = getCorner(BottomLeft,  stack);

    bool top_check      = plug::cross(tl - tr, position - tr) <= 0.0;
    bool right_check    = plug::cross(tr - br, position - br) <= 0.0;
    bool bottom_check   = plug::cross(br - bl, position - bl) <= 0.0;
    bool left_check     = plug::cross(bl - tl, position - tl) <= 0.0;

    return top_check && right_check && bottom_check && left_check;

    return false;
}

void Widget::onTick(const plug::TickEvent &event, plug::EHC &context)
{
    onTime(event.delta_time, context);
}

void Widget::onMouseMove(const plug::MouseMoveEvent &event, plug::EHC &context)
{
    onMouseMoved(event.pos.x, event.pos.y, context);
}

void Widget::onMousePressed(const plug::MousePressedEvent &event, plug::EHC &context)
{
    onMousePressed(event.button_id, event.pos.x, event.pos.y, context);
}

void Widget::onMouseReleased(const plug::MouseReleasedEvent &event, plug::EHC &context)
{
    onMouseReleased(event.button_id, event.pos.x, event.pos.y, context);
}

void Widget::onKeyboardPressed(const plug::KeyboardPressedEvent &event, plug::EHC &context)
{
    onKeyboardPressed(event.key_id, context);
}

void Widget::onKeyboardReleased(const plug::KeyboardReleasedEvent &event, plug::EHC &context)
{
    onKeyboardReleased(event.key_id, context);
}

void Widget::onResize(const ResizeEvent &event, plug::EHC &context)
{
    onResize(event.size.x, event.size.y, context);
}

