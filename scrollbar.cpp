#include "scrollbar.hpp"

ScrollBar::ScrollButton::ScrollButton(ScrollBar &scrollbar, scroll_button_t btn_type, ButtonTexture &btn_texture) :
    Button
    {
        btn_type == VER ? Vector2f{scrollbar.m_width, scrollbar.m_thickness} : Vector2f{scrollbar.m_thickness, scrollbar.m_height},
        btn_type == VER ? scrollbar.m_thickness : ((scrollbar.m_height / scrollbar.m_wrappee->m_size.y) * (scrollbar.m_height - 2 * scrollbar.m_thickness)),
        btn_type == VER ? ((scrollbar.m_width / scrollbar.m_wrappee->m_size.x) * (scrollbar.m_width - 2 * scrollbar.m_thickness)) : scrollbar.m_thickness,
        btn_texture
    },
    m_type(btn_type),
    m_status(DEFAULT),
    m_hold_pos{0, 0},
    m_scrollbar(&scrollbar)
{}

bool ScrollBar::ScrollButton::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = Button::onMousePressed(key, x, y, transf_list);

    if (res)
    {
        m_status = HOLD;

        transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
        Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

        Vector2f pos = top_transf.applyTransform({x, y});
        m_hold_pos = pos;

        transf_list.PopBack();
    }

    return res;
}

bool ScrollBar::ScrollButton::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = Button::onMouseReleased(key, x, y, transf_list);
    m_status = DEFAULT;

    return res;
}

bool ScrollBar::ScrollButton::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    Button::onMouseMoved(x, y, transf_list);

    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    if (m_status == HOLD)
    {
        Vector2f delta_hold_pos = pos - m_hold_pos;

        if (m_type == VER)
        {
            float prev = m_transf.m_offset.y;
            m_transf.m_offset.y += delta_hold_pos.y * m_transf.m_scale.y;

            if (!(EPS + m_scrollbar->m_thickness < m_transf.m_offset.y &&
                  m_transf.m_offset.y < m_scrollbar->m_height - m_scrollbar->m_thickness - m_size.y - EPS))
                m_transf.m_offset.y = prev;
        }

        if (m_type == HOR)
        {
            float prev = m_transf.m_offset.x;
            m_transf.m_offset.x += delta_hold_pos.x * m_transf.m_scale.x;

            if (!(EPS + m_scrollbar->m_thickness < m_transf.m_offset.x &&
                  m_transf.m_offset.x < m_scrollbar->m_width - m_scrollbar->m_thickness - m_size.x - EPS))
                m_transf.m_offset.x = prev;
        }
    }

    transf_list.PopBack();

    return true;
}

// ==========================================

ScrollBar::ScrollBar(Widget &wrappee, float thickness, float width, bool is_hor, float height, bool is_ver, ScrollBarTexture &texture) :
    Widget
    {
        {wrappee.getTransform().m_offset, {1, 1}},
        Vector2f{(is_hor ? width : wrappee.m_size.x) + (is_ver ? thickness : 0), 
                 (is_ver ? height : wrappee.m_size.y) + (is_hor ? thickness : 0)}
    },
    m_wrappee(&wrappee),
    m_thickness(thickness),
    m_width(is_hor ? width : wrappee.m_size.x),
    m_height(is_ver ? height : wrappee.m_size.y),
    m_is_ver(is_ver),
    m_is_hor(is_hor),
    m_texture(&texture),
    m_btn_ver  (*this, VER, *texture.m_btn_scroll),
    // m_btn_up   (*this, VER, texture.m_btn_up),
    // m_btn_down (*this, VER, texture.m_btn_down),
    m_btn_hor  (*this, HOR, *texture.m_btn_scroll)
    // m_btn_left (*this, HOR, texture.m_btn_left),
    // m_btn_right(*this, HOR, texture.m_btn_right)
{
    wrappee.setTransform
    (
        Transform
        {
            Vector2f{0, 0},
            wrappee.m_transf.m_scale
        }
    );
}

void ScrollBar::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    m_wrappee->draw(target, transf_list);

    if (m_is_ver)
        m_btn_ver.draw(target, transf_list);

    if (m_is_hor)
        m_btn_hor.draw(target, transf_list);

    transf_list.PopBack();
}

bool ScrollBar::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    m_wrappee->onMousePressed(key, x, y, transf_list);

    m_btn_ver.onMousePressed(key, x, y, transf_list);
    m_btn_hor.onMousePressed(key, x, y, transf_list);

    transf_list.PopBack();
}

bool ScrollBar::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    m_wrappee->onMouseReleased(key, x, y, transf_list);

    m_btn_ver.onMouseReleased(key, x, y, transf_list);
    m_btn_hor.onMouseReleased(key, x, y, transf_list);

    transf_list.PopBack();
}

bool ScrollBar::onResize(float width, float height)
{
    //m_size = {width, height};
    //updateVertexArray();

    //m_wrappee->onResize(width - 2 * m_thickness, height - 2 * m_thickness);
}

bool ScrollBar::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.applyTransform({x, y});

    m_wrappee->onMouseMoved(x, y, transf_list);

    m_btn_ver.onMouseMoved(x, y, transf_list);
    m_btn_hor.onMouseMoved(x, y, transf_list);

    transf_list.PopBack();
}

bool ScrollBar::onKeyboardPressed(KeyboardKey key)
{
    m_wrappee->onKeyboardPressed(key);
}

bool ScrollBar::onKeyboardReleased(KeyboardKey key)
{
    m_wrappee->onKeyboardReleased(key);
}

bool ScrollBar::onTime(float d_seconds)
{
    m_wrappee->onTime(d_seconds);
}

