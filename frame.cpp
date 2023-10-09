#include "frame.hpp"

Frame::Frame(Widget &wrappee, const char *title, float thickness, float width, float height) :
    Widget({wrappee.getTransform().m_offset, Vector2f{2 * thickness + width, 2 * thickness + height}}, {width, height}),
    m_wrappee(&wrappee),
    m_title(title),
    m_thickness(thickness),
    m_width(width),
    m_height(height),
    m_vertex_array(sf::Quads, 4),
    m_status(DEFAULT)
{
    m_vertex_array[0].position = {0, 0};
    m_vertex_array[1].position = {1, 0};
    m_vertex_array[2].position = {1, 1};
    m_vertex_array[3].position = {0, 1};

    wrappee.setTransform
    (
        Transform
        {
            Vector2f{thickness / (2 * thickness + width), thickness / (2 * thickness + height)},
            wrappee.getTransform().m_scale
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

    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < m_wrappee->getTransform().m_offset.y - EPS)
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

