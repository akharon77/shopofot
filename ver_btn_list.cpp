#include "ver_btn_list.hpp"

VerticalButtonList::VerticalButtonList(Vector2f pos) :
    Widget
    {
        {pos, {1, 1}},
        {0, 0}
    }
{}

void VerticalButtonList::addButton(Button &btn)
{
    btn.m_transf.m_offset = {0, m_size.y};
    m_size.y += btn.m_size.y;

    m_btn_list.PushBack(&btn);

    if (btn.m_size.x > m_size.x + EPS)
        m_size.x = btn.m_size.x;
}

void VerticalButtonList::draw(sf::RenderTarget &target, List<Transform> &transf_list)
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

    transf_list.PopBack();
}

bool VerticalButtonList::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
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

    transf_list.PopBack();

    return true;
}

bool VerticalButtonList::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
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

    transf_list.PopBack();

    return true;
}

bool VerticalButtonList::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
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

    transf_list.PopBack();

    return true;
}

bool VerticalButtonList::onResize(float width, float height)
{
    return false;
}

bool VerticalButtonList::onKeyboardPressed(KeyboardKey key)
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

    return true; 
}

bool VerticalButtonList::onKeyboardReleased(KeyboardKey key)
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

    return true;
}

bool VerticalButtonList::onTime(float d_seconds)
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

    return true;
}

