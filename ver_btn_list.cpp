#include "universal_layout_box.hpp"
#include "ver_btn_list.hpp"

VerticalButtonList::VerticalButtonList(const LayoutBox &box, const char *str, TextButtonTexture &btn_texture) :
    TextButton(box, str, btn_texture),
    m_status(DEFAULT),
    m_bottom(0)
{}

int32_t VerticalButtonList::addButton(Button &btn)
{
    Vec2d own_size = getLayoutBox().getSize();
    Vec2d prev_btn_size = btn.getLayoutBox().getSize();

    btn.setLayoutBox(UniversalLayoutBox(0_px, 0_px));
    btn.getLayoutBox().setPosition(Vec2d(0, own_size.y + m_bottom));

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

void VerticalButtonList::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    TextButton::draw(target, transf_list);

    if (m_status != OPENED)
        return;

    transf_list.PushBack(Transform(getLayoutBox().getPosition(), Vec2d(1, 1)).combine(transf_list.Get(transf_list.GetTail())->val));
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
        transf_list.PushBack(Transform(getLayoutBox().getPosition(), Vec2d(1, 1)).combine(transf_list.Get(transf_list.GetTail())->val));
        Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

        int32_t anch = m_btn_lst.GetHead();
        Node<Button*> node = *m_btn_lst.Get(anch);

        int32_t size = m_btn_lst.GetSize();
        for (int32_t i = 0; i < size; ++i)
        {
            res = node.val->onMousePressed(key, x, y, transf_list) || res;
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

    transf_list.PushBack(Transform(getLayoutBox().getPosition(), Vec2d(1, 1)).combine(transf_list.Get(transf_list.GetTail())->val));
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

    transf_list.PushBack(Transform(getLayoutBox().getPosition(), Vec2d(1, 1)).combine(transf_list.Get(transf_list.GetTail())->val));
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

