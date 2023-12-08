#include "toolbar.hpp"
#include "universal_layoutbox.hpp"

ToolButton::ToolButton(const plug::LayoutBox &box, ButtonTexture &btn_texture, ToolPalette &tool_palette, int32_t tool_id) :
    ToggleButton(box, btn_texture),
    m_tool_palette(&tool_palette),
    m_tool_id(tool_id)
{}

void ToolButton::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    ToggleButton::onMousePressed(key, x, y, context);
    if (context.stopped)
        m_tool_palette->setActiveTool(m_tool_id);
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

void ToolBar::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    stack.enter(own_transf);

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(stack, target);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    stack.leave();
}

void ToolBar::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMousePressed(key, x, y, context);
        if (context.stopped)
        {
            setToggled(anch);
            return;
        }

        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    context.stack.leave();
}

void ToolBar::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseReleased(key, x, y, context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    context.stack.leave();
}

void ToolBar::onMouseMoved(double x, double y, plug::EHC &context)
{
    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_btn_list.GetHead();
    Node<ToolButton*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseMoved(x, y, context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    context.stack.leave();
}

