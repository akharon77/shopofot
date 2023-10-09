#include "frame.hpp"

Frame::Frame(Widget &wrappee, const char *title, float thickness, const ButtonTexture &close_btn_texture) :
    Widget
    {
        {wrappee.getTransform().m_offset, {1, 1}},
        wrappee.m_size + 2.f * Vector2f{thickness, thickness}
    },
    m_wrappee(&wrappee),
    m_title(title),
    m_thickness(thickness),
    m_vertex_array(sf::Quads, 4),
    m_status(DEFAULT),
    m_close_btn(*this, close_btn_texture)
{
    m_vertex_array[0].position = {0, 0};
    m_vertex_array[1].position = {m_size.x, 0};
    m_vertex_array[2].position = {m_size.x, m_size.y};
    m_vertex_array[3].position = {0, m_size.y};

    wrappee.setTransform
    (
        Transform
        {
            Vector2f{thickness, thickness},
            wrappee.m_transf.m_scale
        }
    );
}

void Frame::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    sf::VertexArray buf_vertex_array(m_vertex_array);
    for (int32_t i = 0; i < buf_vertex_array.getVertexCount(); ++i)
        buf_vertex_array[i].position = top_transf.rollbackTransform(m_vertex_array[i].position);

    target.draw(buf_vertex_array);
    m_wrappee->draw(target, transf_list);

    transf_list.PopBack();
}

bool Frame::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    if (EPS < pos.x && pos.x < m_wrappee->m_size.x + 2 * m_thickness - EPS &&
        EPS < pos.y && pos.y < m_thickness - EPS)
    {
        m_status = HOLD;
        m_hold_pos = pos;
    }

    m_wrappee->onMousePressed(key, x, y, transf_list);

    transf_list.PopBack();
}

bool Frame::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    if (m_status == HOLD)
        m_status = DEFAULT;

    m_wrappee->onMouseReleased(key, x, y, transf_list);

    transf_list.PopBack();
}

bool Frame::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    if (m_status == HOLD)
    {
        Vector2f delta_hold_pos = pos - m_hold_pos;
        m_transf.m_offset += Vector2f{delta_hold_pos.x * m_transf.m_scale.x, delta_hold_pos.y * m_transf.m_scale.y};
    }

    m_wrappee->onMouseMoved(x, y, transf_list);

    transf_list.PopBack();
}

bool Frame::onKeyboardPressed(KeyboardKey key)
{
    m_wrappee->onKeyboardPressed(key);
}

bool Frame::onKeyboardReleased(KeyboardKey key)
{
    m_wrappee->onKeyboardReleased(key);
}

bool Frame::onTime(float d_seconds)
{
    m_wrappee->onTime(d_seconds);
}

