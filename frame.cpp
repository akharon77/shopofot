#include "frame.hpp"

Frame::Frame(Widget &wrappee, const char *title, float thickness, float width, float height) :
    m_wrappee(&wrappee),
    m_title(title),
    m_thickness(thickness),
    m_width(width),
    m_height(height),
    m_transf(wrappee->getTransform().m_offset, Vector2f{2 * thickness + width, 2 * thickness + height}),
    m_vertex_array(sf::Quads, 4)
{
    m_vertex_array[0].position = {0, 0};
    m_vertex_array[1].position = {1, 0};
    m_vertex_array[2].position = {1, 1};
    m_vertex_array[3].position = {0, 1};

    wrappee->setTransform
    (
        Transform
        {
            Vector2f{thickness / (2 * thickness + width), thickness / (2 * thickness + height)},
            wrappee->getTransform().m_scale
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

    transf_list.PopBack();
}

bool onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    m_wrappee->onMousePressed(pos.x, pos.y, transf_list);

    transf_list.PopBack();
}

bool onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    m_wrappee->onMouseReleased(pos.x, pos.y, transf_list);

    transf_list.PopBack();
}

bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    m_wrappee->onMouseMoved(pos.x, pos.y, transf_list);

    transf_list.PopBack();
}

bool onKeyboardPressed(KeyboardKey key)
{
    m_wrappee->onKeyboardPressed(key);
}

bool onKeyboardReleased(KeyboardKey key)
{
    m_wrappee->onKeyboardReleased(key);
}

bool onTime (float d_seconds)
{
    m_wrappee->onTime(d_seconds);
}

