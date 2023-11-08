#include "toolbar.hpp"

ToolButton::ToolButton(Vector2f pos, float width, float height, ButtonTexture &btn_texture, ToolPalette &tool_palette, int32_t tool_id) :
    ToggleButton(pos, width, height, btn_texture),
    m_tool_palette(&tool_palette),
    m_tool_id(tool_id)
{}

bool ToolButton::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = ToggleButton::onMousePressed(key, x, y, transf_list);
    if (res)
        m_tool_palette->setActiveTool(m_tool_id);

    return res;
}

ToolBar::ToolBar(Vector2f pos, float btn_width, float btn_height, ToolPalette &tool_palette, int32_t cnt_x) :
    Widget({pos, {1, 1}}, {0, 0}),
    m_btn_width(btn_width),
    m_btn_height(btn_height),
    m_tool_palette(&tool_palette),
    m_cnt_x(cnt_x),
    m_toggled_id(-1)
{}

void ToolBar::addButton(ButtonTexture &btn_texture, int32_t tool_id)
{
    int32_t cnt = m_btn_list.GetSize();

    int32_t x = cnt % m_cnt_x;
    int32_t y = cnt / m_cnt_x;

    m_size.x = std::max(m_size.x, m_btn_width * x);
    m_size.y = std::max(m_size.y, m_btn_height * y);

    ToolButton *btn = new ToolButton({x * m_btn_width, y * m_btn_height}, m_btn_width, m_btn_height, btn_texture, *m_tool_palette, tool_id);
    setToggled(m_btn_list.PushBack(btn));
}

void ToolBar::setToggled(int32_t id)
{
    if (m_toggled_id != -1)
        m_btn_list.Get(m_toggled_id)->val->setToggle(false);

    m_toggled_id = id;
}

void ToolBar::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(target, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    transf_list.PopBack();
}

bool ToolBar::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    // bool res = false;

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        if (node.val->onMousePressed(key, x, y, transf_list))
        {
            setToggled(anch);
            transf_list.PopBack();
            return true;
        }

        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    transf_list.PopBack();

    return false;
}

bool ToolBar::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseReleased(key, x, y, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    transf_list.PopBack();

    return true;
}

bool ToolBar::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseMoved(x, y, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    transf_list.PopBack();

    return true;
}

