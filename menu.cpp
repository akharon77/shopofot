#include "menu.hpp"

Menu::Menu(Widget &wrappee) :
    Widget(UniversalLayoutBox(0_px, 0_px)),
    // {
    //     {wrappee.m_transf.m_offset, {1, 1}},
    //     wrappee.m_size
    // },
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
    // btn.m_transf.m_offset = {m_right_corner, 0};
    m_right_corner += btn_size.x;
    m_btn_list.PushBack(&btn);

    if (btn_size.y > m_max_height + EPS)
    {
        m_max_height = btn_size.y;

        Vec2d prev_wrappee_pos = m_wrappee->getLayoutBox().getPosition();
        prev_wrappee_pos.y = m_max_height;
        m_wrappee->getLayoutBox().setPosition(prev_wrappee_pos);
        // m_wrappee->m_transf.m_offset.y = m_max_height;

        Vec2d prev_size = getLayoutBox().getSize();
        prev_size.y = m_wrappee->getLayoutBox().getSize().y + m_max_height;
        getLayoutBox().setSize(prev_size);
        // m_size.y = m_wrappee->m_size.y + m_max_height;
    }
}

void Menu::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    m_wrappee->draw(target, transf_list);

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(target, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    transf_list.PopBack();
}

bool Menu::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    bool res = false;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        res = node.val->onMousePressed(key, x, y, transf_list) || res;
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    res = res || m_wrappee->onMousePressed(key, x, y, transf_list);

    transf_list.PopBack();

    return res;
}

bool Menu::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseReleased(key, x, y, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onMouseReleased(key, x, y, transf_list);

    transf_list.PopBack();

    return true;
}

bool Menu::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseMoved(x, y, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onMouseMoved(x, y, transf_list);

    transf_list.PopBack();

    return true;
}

bool Menu::onResize(float width, float height)
{
    if (width < m_right_corner)
        return false;

    bool res = m_wrappee->onResize(width, height - m_max_height);

    // m_size = {width, height};
    getLayoutBox().setSize(Vec2d(width, height));

    return res;
}

bool Menu::onKeyboardPressed(KeyboardKey key)
{
    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onKeyboardPressed(key);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onKeyboardPressed(key);

    return true; 
}

bool Menu::onKeyboardReleased(KeyboardKey key)
{
    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onKeyboardReleased(key);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onKeyboardReleased(key);

    return true;
}

bool Menu::onTime(float d_seconds)
{
    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onTime(d_seconds);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onTime(d_seconds);

    return true;
}

