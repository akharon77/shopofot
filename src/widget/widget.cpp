#include "widget.hpp"
#include "graphics/vertex_array.hpp"

Widget::Widget(const LayoutBox &box) :
    m_layout_box(box.clone())
{}

void Widget::onParentUpdate(const LayoutBox &parent_box)
{
    m_layout_box->onParentUpdate(parent_box);
}

LayoutBox& Widget::getLayoutBox()
{
    return *m_layout_box;
}

const LayoutBox& Widget::getLayoutBox() const
{
    return *m_layout_box;
}

void Widget::setLayoutBox(const LayoutBox &box)
{
    delete m_layout_box;
    m_layout_box = box.clone();
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
    switch (event.getType()) {
        case plug::EventType::Tick: {
                                        onTick((const plug::TickEvent &)event, context);
                                    } break;
        case plug::EventType::KeyboardPressed: {
                                                   onKeyboardPressed((const plug::KeyboardPressedEvent &)event, context);
                                               } break;
        case plug::EventType::KeyboardReleased: {
                                                    onKeyboardReleased((const plug::KeyboardReleasedEvent &)event, context);
                                                } break;
        case plug::EventType::MousePressed: {
                                                onMousePressed((const plug::MousePressedEvent &)event, context);
                                            } break;
        case plug::EventType::MouseReleased: {
                                                 onMouseReleased((const plug::MouseReleasedEvent &)event, context);
                                             } break;
        case plug::EventType::MouseMove: {
                                             onMouseMove((const plug::MouseMoveEvent &)event, context);
                                         } break;
        default:
                                         break;
    }
}
