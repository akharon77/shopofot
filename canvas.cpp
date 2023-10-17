#include "canvas.hpp"
#include "tool.hpp"

Canvas::Canvas(Vector2f pos, float width, float height, int32_t canv_width, int32_t canv_height, Tool *tool) :
    Widget({pos, Vector2f{width, height}}, {width, height}),
    m_width  (width),
    m_height (height),
    m_canv_width(canv_width),
    m_canv_height(canv_height),
    m_vertex_arr(sf::Quads, 4),
    m_tool(tool)
{
    m_canv_texture.create(canv_width, canv_height);
    m_canv_texture.clear(sf::Color::Black);

    m_vertex_arr[0].position = {0, 0};
    m_vertex_arr[1].position = {1, 0};
    m_vertex_arr[2].position = {1, 1};
    m_vertex_arr[3].position = {0, 1};
    
    m_vertex_arr[0].texCoords = {0,          0};
    m_vertex_arr[1].texCoords = {canv_width, 0};
    m_vertex_arr[2].texCoords = {canv_width, canv_height};
    m_vertex_arr[3].texCoords = {0,          canv_height};
}

void Canvas::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    sf::VertexArray buf_vertex_arr(m_vertex_arr);
    for (int32_t i = 0; i < 4; ++i)
        buf_vertex_arr[i].position = top_transf.rollbackTransform(buf_vertex_arr[i].position);

    m_canv_texture.display();
    target.draw(buf_vertex_arr, &m_canv_texture.getTexture());

    m_tool->getWidget()->draw(target, transf_list);

    transf_list.PopBack();
}

bool Canvas::onResize(float width, float height)
{
    m_size = {width, height};
    m_width = width;
    m_height = height;

    return true;
}

bool Canvas::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) 
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});
    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        Vector2f pos = top_transf.applyTransform({x, y});
        m_tool->onMainButton(key, pos, *this);

        m_tool->getWidget()->onMousePressed(key, x, y, transf_list);

        transf_list.PopBack();
        return true;
    }

    transf_list.PopBack();
    return false;
}

bool Canvas::onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    m_tool->onMainButton(key, top_transf.applyTransform({x, y}), *this);
    m_tool->getWidget()->onMouseReleased(key, x, y, transf_list);
    return true;
}

bool Canvas::onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});
    m_tool->onMove(pos, *this);

    m_tool->getWidget()->onMouseMoved(x, y, transf_list);

    transf_list.PopBack();
    return false;
}

bool Canvas::onKeyboardPressed  (KeyboardKey key) {};
bool Canvas::onKeyboardReleased (KeyboardKey key) {};

bool Canvas::onTime (float d_seconds) {};
