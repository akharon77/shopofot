#include "ui/button/vertical_button_list.hpp"
#include "universal_layoutbox.hpp"

VerticalButtonList::VerticalButtonList(const plug::LayoutBox &box, const char *str, TextButtonTexture &btn_texture) :
    TextButton(box, str, btn_texture),
    m_status(DEFAULT),
    m_bottom(0)
{}

int32_t VerticalButtonList::addButton(Button &btn)
{
    plug::Vec2d own_size = getLayoutBox().getSize();
    plug::Vec2d prev_btn_size = btn.getLayoutBox().getSize();

    btn.setLayoutBox(UniversalLayoutBox(0_px, 0_px));
    btn.getLayoutBox().setSize(prev_btn_size);
    btn.getLayoutBox().setPosition(plug::Vec2d(0, own_size.y + m_bottom));

    m_bottom += prev_btn_size.y;
    return m_btn_lst.PushBack(&btn);
}

Button *VerticalButtonList::popButton()
{
    if (m_btn_lst.GetSize() == 0)
        return nullptr;

    int32_t anch = m_btn_lst.GetTail();
    Button* res = m_btn_lst.Get(anch)->val;
    m_bottom -= res->getLayoutBox().getSize().y;
    m_btn_lst.Erase(anch);
    return res;
}

void VerticalButtonList::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    TextButton::draw(stack, target);

    if (m_status != OPENED)
        return;

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    stack.enter(own_transf);

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(stack, target);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    stack.leave();
}

void VerticalButtonList::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    TextButton::onMousePressed(key, x, y, context);

    if (context.stopped)
    {
        if (m_status == OPENED)
            m_status = DEFAULT;
        else
            m_status = OPENED;
    }
    else if (m_status == OPENED)
    {
        plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
        context.stack.enter(own_transf);

        int32_t anch = m_btn_lst.GetHead();
        Node<Button*> node = *m_btn_lst.Get(anch);

        int32_t size = m_btn_lst.GetSize();
        for (int32_t i = 0; i < size; ++i)
        {
            node.val->onMousePressed(key, x, y, context);
            anch = node.next;
            node = *m_btn_lst.Get(anch);
        }

        context.stack.leave();

        if (!context.stopped)
            m_status = DEFAULT;
    }
}

void VerticalButtonList::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    TextButton::onMouseReleased(key, x, y, context);

    if (m_status == OPENED)
    {
        context.stopped = true;
        return;
    }

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseReleased(key, x, y, context);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    context.stack.leave();
}

void VerticalButtonList::onMouseMoved(double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    TextButton::onMouseMoved(x, y, context);

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseMoved(x, y, context);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    context.stack.leave();
}

void VerticalButtonList::onKeyboardPressed(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onKeyboardPressed(key, context);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }
}

void VerticalButtonList::onKeyboardReleased(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onKeyboardReleased(key, context);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }
}

void VerticalButtonList::onTime(double d_seconds, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onTime(d_seconds, context);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }
}

