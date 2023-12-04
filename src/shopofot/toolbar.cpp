#include "toolbar.hpp"
#include "universal_layout_box.hpp"

ToolButton::ToolButton(const LayoutBox &box, ButtonTexture &btn_texture, ToolPalette &tool_palette, int32_t tool_id) :
    ToggleButton(box, btn_texture),
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

ToolBar::ToolBar(double btn_width, double btn_height, ToolPalette &tool_palette, int32_t cnt_x) :
    Widget(UniversalLayoutBox(0_px, 0_px)),
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

    Vec2d own_size = getLayoutBox().getSize();
    own_size.x = std::max(own_size.x, m_btn_width  * (x + 1));
    own_size.y = std::max(own_size.y, m_btn_height * (y + 1));
    getLayoutBox().setSize(own_size);

    UniversalLayoutBox tool_btn_box(0_px, 0_px);
    tool_btn_box.setPosition(Vec2d(x * m_btn_width, y * m_btn_height));
    tool_btn_box.setSize(Vec2d(m_btn_width, m_btn_height));
    ToolButton *btn = new ToolButton(tool_btn_box, btn_texture, *m_tool_palette, tool_id);
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
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
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
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
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
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
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
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
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

