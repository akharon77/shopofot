#include "ver_btn_list.hpp"

VerticalButtonList::VerticalButtonList(Vector2f pos, float width, float height, const char *str, sf::Font &font, int32_t char_size, const ButtonTexture &btn_texture) :
    TextButton(pos, width, height, str, font, char_size, btn_texture),
    m_status(DEFAULT),
    m_bottom(0)
{}

void VerticalButtonList::addButton(Button &btn)
{
    btn.m_transf.m_offset = {0, m_size.y + m_bottom};
    // btn.m_transf.m_scale.x /= m_width;
    // btn.m_transf.m_scale.y /= m_height;
    m_bottom += btn.m_size.y;
    m_btn_lst.PushBack(&btn);
}

void VerticalButtonList::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    TextButton::draw(target, transf_list);

    if (m_status != OPENED)
        return;

    transf_list.PushBack(Transform(m_transf.m_offset, {1, 1}).applyParent(transf_list.Get(transf_list.GetTail())->val));
    //transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(target, transf_list);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    //transf_list.PopBack();
    transf_list.PopBack();
}

bool VerticalButtonList::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = TextButton::onMousePressed(key, x, y, transf_list);

    if (res)
    {
        if (m_status == OPENED)
            m_status = DEFAULT;
        else
            m_status = OPENED;
    }
    else if (m_status == OPENED)
    {
        transf_list.PushBack(Transform(m_transf.m_offset, {1, 1}).applyParent(transf_list.Get(transf_list.GetTail())->val));
        //transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
        Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

        int32_t anch = m_btn_lst.GetHead();
        Node<Button*> node = *m_btn_lst.Get(anch);

        int32_t size = m_btn_lst.GetSize();
        for (int32_t i = 0; i < size; ++i)
        {
            res = res || node.val->onMousePressed(key, x, y, transf_list);
            anch = node.next;
            node = *m_btn_lst.Get(anch);
        }

        transf_list.PopBack();

        if (!res)
            m_status = DEFAULT;
    }

    return res;
}

bool VerticalButtonList::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    TextButton::onMouseReleased(key, x, y, transf_list);

    if (m_status != OPENED)
        return true;

    transf_list.PushBack(Transform(m_transf.m_offset, {1, 1}).applyParent(transf_list.Get(transf_list.GetTail())->val));
    //transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseReleased(key, x, y, transf_list);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    transf_list.PopBack();

    return true;
}

bool VerticalButtonList::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    TextButton::onMouseMoved(x, y, transf_list);

    transf_list.PushBack(Transform(m_transf.m_offset, {1, 1}).applyParent(transf_list.Get(transf_list.GetTail())->val));
    //transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onMouseMoved(x, y, transf_list);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    transf_list.PopBack();

    return true;
}

bool VerticalButtonList::onKeyboardPressed(KeyboardKey key)
{
    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onKeyboardPressed(key);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    return true; 
}

bool VerticalButtonList::onKeyboardReleased(KeyboardKey key)
{
    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onKeyboardReleased(key);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    return true;
}

bool VerticalButtonList::onTime(float d_seconds)
{
    int32_t anch = m_btn_lst.GetHead();
    Node<Button*> node = *m_btn_lst.Get(anch);

    int32_t size = m_btn_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->onTime(d_seconds);
        anch = node.next;
        node = *m_btn_lst.Get(anch);
    }

    return true;
}

