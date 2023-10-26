#include "menu.hpp"

Menu::Menu(Widget &wrappee) :
    Widget
    {
        {wrappee.m_transf.m_offset, {1, 1}},
        wrappee.m_size
    },
    m_wrappee(&wrappee),
    m_right_corner(0),
    m_max_height(0)
{
    wrappee.m_transf.m_offset = {0, 0};
}

void Menu::addButton(Button &btn)
{
    btn.m_transf.m_offset = {m_right_corner, 0};
    m_right_corner += btn.m_size.x;
    m_btn_list.PushBack(&btn);

    if (btn.m_size.y > m_max_height + EPS)
    {
        m_max_height = btn.m_size.y;
        m_wrappee->m_transf.m_offset.y = m_max_height;
        m_size.y = m_wrappee->m_size.y + m_max_height;
    }
}

void Menu::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(target, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->draw(target, transf_list);

    transf_list.PopBack();
}

bool Menu::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_list.GetHead();
    Node<Button*> node = *m_btn_list.Get(anch);

    int32_t size = m_btn_list.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMousePressed(key, x, y, transf_list);
        anch = node.next;
        node = *m_btn_list.Get(anch);
    }

    m_wrappee->onMousePressed(key, x, y, transf_list);

    transf_list.PopBack();

    return true;
}

bool Menu::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
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
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
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

    m_size = {width, height};

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

