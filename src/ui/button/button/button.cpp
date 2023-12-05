#include "ui/button/button.hpp"

Button::Button(const LayoutBox &box, const ButtonTexture &btn_texture) :
    Widget(box),
    m_status(DEFAULT),
    m_btn_texture(btn_texture),
    m_vertex_array(plug::PrimitiveType::Quads, 4)
{
    m_vertex_array[0].position = plug::Vec2d(0, 0);
    m_vertex_array[1].position = plug::Vec2d(1, 0);
    m_vertex_array[2].position = plug::Vec2d(1, 1);
    m_vertex_array[3].position = plug::Vec2d(0, 1);

    setRect(m_btn_texture.m_default_rect);
}

void Button::setRect(const Rect &rect)
{
    m_vertex_array[0].tex_coords = plug::Vec2d(rect.left, rect.top);
    m_vertex_array[1].tex_coords = plug::Vec2d(rect.left + rect.width, rect.top);
    m_vertex_array[2].tex_coords = plug::Vec2d(rect.left + rect.width, rect.top + rect.height);
    m_vertex_array[3].tex_coords = plug::Vec2d(rect.left, rect.top + rect.height);
}
 
void Button::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    plug::Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    stack.enter(own_transf);

    plug::VertexArray buf_vertex_array(m_vertex_array);
    for (int32_t i = 0; i < 4; ++i)
        buf_vertex_array[i].position = stack.apply(m_vertex_array[i].position);

    target.draw(buf_vertex_array, *m_btn_texture.m_texture);

    stack.leave();
}

void Button::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    plug::Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    plug::Vec2d pos = context.stack.restore(plug::Vec2d(x, y));

    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        m_status = PRESSED;
        setRect(m_btn_texture.m_pressed_rect);

        context.stack.leave();
        context.stopped = true;
        return;
    }

    context.stack.leave();
}

void Button::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    plug::Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    plug::Vec2d pos = context.stack.restore(plug::Vec2d(x, y));

    if (m_status == PRESSED)
    {
        context.stopped = true;

        if (EPS < pos.x && pos.x < 1 - EPS &&
            EPS < pos.y && pos.y < 1 - EPS)
        {
            m_status = FOCUSED;
            setRect(m_btn_texture.m_focused_rect);

            context.stack.leave();
            context.overlapped = true;
            return;
        }
        else
        {
            m_status = DEFAULT;
            setRect(m_btn_texture.m_default_rect);
        }
    }

    context.stack.leave();
}

void Button::onMouseMoved(double x, double y, plug::EHC &context)
{
    Transform m_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    bool res = false;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (m_status == DEFAULT            &&
        EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        m_status = FOCUSED;
        res = true;
        setRect(m_btn_texture.m_focused_rect);
    }
    else if (m_status != DEFAULT              &&
             !(EPS < pos.x && pos.x < 1 - EPS &&
               EPS < pos.y && pos.y < 1 - EPS))
    {
        m_status = DEFAULT;
        res = true;
        setRect(m_btn_texture.m_default_rect);
    }

    transf_list.PopBack();
    return res;
}

bool Button::onResize(float width, float height)
{
    // m_size = {width, height};
    getLayoutBox().setSize(Vec2d(width, height));
    // m_transf.m_scale = m_size;
    // m_width = width;
    // m_height = height;
}

