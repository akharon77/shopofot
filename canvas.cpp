#include "canvas.hpp"
#include "tool.hpp"
#include "filter.hpp"

Canvas::Canvas(const LayoutBox &box, int32_t canv_width, int32_t canv_height, ToolPalette &tool_palette, FilterPalette &filter_palette) :
    Widget(box),
    m_width (0),  // TODO: where is this used?
    m_height(0),
    m_canv_width(canv_width),
    m_canv_height(canv_height),
    m_vertex_arr(sf::Quads, 4),
    m_tool_palette(&tool_palette),
    m_filter_mask(canv_width, canv_height),
    m_filter_palette(&filter_palette),
    m_last_mouse_pos(0, 0)
{
    m_canv_texture.create(canv_width, canv_height);
    m_canv_texture.clear(sf::Color::Black);

    m_vertex_arr[0].position = {0, 0};
    m_vertex_arr[1].position = {1, 0};
    m_vertex_arr[2].position = {1, 1};
    m_vertex_arr[3].position = {0, 1};
    
    updateVertexArray();
}

void Canvas::updateVertexArray()
{
    m_vertex_arr[0].texCoords = {0,            0};
    m_vertex_arr[1].texCoords = {m_canv_width, 0};
    m_vertex_arr[2].texCoords = {m_canv_width, m_canv_height};
    m_vertex_arr[3].texCoords = {0,            m_canv_height};
}

sf::Image Canvas::getImage()
{
    return m_canv_texture.getTexture().copyToImage();
}

void Canvas::drawImage(const sf::Image &image)
{
    sf::Texture buf_texture;
    buf_texture.loadFromImage(image);

    sf::Sprite buf_sprite;
    buf_sprite.setTexture(buf_texture);
    m_canv_texture.draw(buf_sprite);
    m_canv_texture.display();
}

void Canvas::loadFromImage(const sf::Image &image)
{
    sf::Vector2u size = image.getSize();
    resize(size.x, size.y);
    drawImage(image);
}

void Canvas::resize(uint32_t width, uint32_t height)
{
    m_canv_width = width;
    m_canv_height = height;
    updateVertexArray();

    m_filter_mask.resize(width, height);

    m_canv_texture.create(width, height);
}

void Canvas::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox()->getPosition(), getLayoutBox()->getSize());

    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    sf::VertexArray buf_vertex_arr(m_vertex_arr);
    for (int32_t i = 0; i < 4; ++i)
        buf_vertex_arr[i].position = top_transf.rollbackTransform(buf_vertex_arr[i].position);

    m_canv_texture.display();
    target.draw(buf_vertex_arr, &m_canv_texture.getTexture());

    Widget *tool_widget = m_tool_palette->getActiveTool()->getWidget();
    if (tool_widget != nullptr)
        tool_widget->draw(target, transf_list);

    transf_list.PopBack();
}

// deprecated
bool Canvas::onResize(float width, float height)
{
    m_size = {width, height};
    m_width = width;
    m_height = height;

    return true;
}

bool Canvas::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) 
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox()->getPosition(), getLayoutBox()->getSize());

    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});
    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        Tool *tool = m_tool_palette->getActiveTool();
        tool->onMainButton(MouseType::PRESSED, pos, *this);

        Widget *tool_widget = tool->getWidget();
        if (tool_widget != nullptr)
            tool_widget->onMousePressed(key, x, y, transf_list);

        transf_list.PopBack();
        return true; 
    }

    transf_list.PopBack();
    return false;
}

bool Canvas::onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox()->getPosition(), getLayoutBox()->getSize());

    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Tool *tool = m_tool_palette->getActiveTool();
    tool->onMainButton(MouseType::RELEASED, top_transf.applyTransform({x, y}), *this);
    Widget *tool_widget = tool->getWidget();
    if (tool_widget != nullptr)
        tool_widget->onMouseReleased(key, x, y, transf_list);

    transf_list.PopBack();
    return true;
}

bool Canvas::onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox()->getPosition(), getLayoutBox()->getSize());

    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});
    m_last_mouse_pos = pos;

    Tool *tool = m_tool_palette->getActiveTool();
    tool->onMove(pos, *this);
    Widget *tool_widget = tool->getWidget();
    if (tool_widget != nullptr)
        tool_widget->onMouseMoved(x, y, transf_list);

    transf_list.PopBack();
    return true;
}

bool Canvas::onKeyboardPressed  (KeyboardKey key)
{
    Tool *tool = m_tool_palette->getActiveTool();
    Widget *tool_widget = tool->getWidget();

    if (key == KeyboardKey::Right)
    {
        m_tool_palette->nextTool();
        return true;
    }

    if (key == KeyboardKey::Enter)
    {
        m_tool_palette->getActiveTool()->onConfirm(m_last_mouse_pos, *this);
        return true;
    }

    if (key == KeyboardKey::Escape)
    {
        m_tool_palette->getActiveTool()->onCancel(m_last_mouse_pos, *this);
    }

    if (key == KeyboardKey::F)
    {
        m_filter_palette->getLastFilter()->applyFilter(*this, m_filter_mask);
    }

    if (tool_widget != nullptr)
        tool_widget->onKeyboardPressed(key);

    return false;
}

bool Canvas::onKeyboardReleased (KeyboardKey key)
{
    Tool *tool = m_tool_palette->getActiveTool();
    Widget *tool_widget = tool->getWidget();

    if (tool_widget != nullptr)
        tool_widget->onKeyboardReleased(key);

    return false;
}

bool Canvas::onTime(float d_seconds)
{
    Tool *tool = m_tool_palette->getActiveTool();
    Widget *tool_widget = tool->getWidget();

    if (tool_widget != nullptr)
        tool_widget->onTime(d_seconds);
}

