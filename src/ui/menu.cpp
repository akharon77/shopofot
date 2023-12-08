#include "ui/menu.hpp"
#include "math/transform_stack.hpp"
#include "universal_layoutbox.hpp"

static const double EPS = 1e-6;
static TransformStack FAKE_STACK;
static plug::EHC FAKE_EHC((plug::TransformStack&) FAKE_STACK, false, false);

Menu::Menu(plug::Widget &wrappee) :
    Widget(UniversalLayoutBox(0_px, 0_px)),
    m_wrappee(&wrappee),
    m_wrappee_stolen_layout_box(wrappee.getLayoutBox().clone()),
    m_right_corner(0),
    m_max_height(0)
{
    Vec2d wrappee_pos  = wrappee.getLayoutBox().getPosition();
    Vec2d wrappee_size = wrappee.getLayoutBox().getSize();

    getLayoutBox().setPosition(wrappee_pos);
    getLayoutBox().setSize(wrappee_size);

    UniversalLayoutBox new_wrappee_box(0_px, 0_px);
    new_wrappee_box.setSize(wrappee_size);
    wrappee.setLayoutBox(new_wrappee_box);
}

void Menu::addButton(Button &btn)
{
    Vec2d btn_size = btn.getLayoutBox().getSize();
    btn.setLayoutBox(UniversalLayoutBox(0_px, 0_px));
    btn.getLayoutBox().setSize(btn_size);
    btn.getLayoutBox().setPosition(Vec2d(m_right_corner, 0));
    m_right_corner += btn_size.x;
    m_btn_list.PushBack(&btn);

    if (btn_size.y > m_max_height + EPS)
    {
        m_max_height = btn_size.y;

        Vec2d prev_wrappee_pos = m_wrappee->getLayoutBox().getPosition();
        prev_wrappee_pos.y = m_max_height;
        m_wrappee->getLayoutBox().setPosition(prev_wrappee_pos);

        Vec2d prev_size = getLayoutBox().getSize();
        prev_size.y = m_wrappee->getLayoutBox().getSize().y + m_max_height;
        getLayoutBox().setSize(prev_size);
    }
}

void Menu::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    stack.enter(own_transf);

    m_wrappee->draw(stack, target);

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(stack, target);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    stack.leave();
}

void Menu::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMousePressed(key, x, y, context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);

    context.stack.leave();
}

void Menu::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseReleased(key, x, y, context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);

    context.stack.leave();
}

void Menu::onMouseMoved(double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);
    
    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseMoved(x, y, context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
    context.stack.leave();
}

void Menu::onResize(double width, double height, plug::EHC &context)
{
    if (width < m_right_corner)
    {
        context.stopped = false;
        return;
    }

    FAKE_EHC.stopped = false;
    m_wrappee->onEvent((const plug::Event&) ResizeEvent(Vec2d(width, height - m_max_height)), context);
    if (!context.stopped)
        return;

    getLayoutBox().setSize(Vec2d(width, height));
}

void Menu::onKeyboardPressed(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onEvent((const plug::Event&) plug::KeyboardPressedEvent(key, false, false, false), context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onEvent((const plug::Event&) plug::KeyboardPressedEvent(key, false, false, false), context);
}

void Menu::onKeyboardReleased(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onEvent((const plug::Event&) plug::KeyboardReleasedEvent(key, false, false, false), context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onEvent((const plug::Event&) plug::KeyboardReleasedEvent(key, false, false, false), context);
}

void Menu::onTime(double d_seconds, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onEvent((const plug::Event&) plug::TickEvent(d_seconds), context);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onEvent((const plug::Event&) plug::TickEvent(d_seconds), context);
}

