#include <type_traits>

#include <SFML/Graphics/RenderTexture.hpp>

#include "universal_layout_box.hpp"
#include "scrollbar.hpp"
#include "window.hpp"

ScrollBar::ScrollDeltaButton::ScrollDeltaButton(ScrollBar &scrollbar, const Vec2d &delta, ButtonTexture &btn_texture) :
    Button(UniversalLayoutBox(), btn_texture),
    m_delta(delta),
    m_scrollbar(scrollbar)
{}

bool ScrollBar::ScrollDeltaButton::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = Button::onMousePressed(key, x, y, transf_list);

    if (res)
        m_scrollbar.deltaPercentageOffset(m_delta);

    return res;
}

ScrollBar::ScrollButton::ScrollButton(ScrollBar &scrollbar, scroll_button_t btn_type, ButtonTexture &btn_texture) :
    Button(UniversalLayoutBox(), btn_texture),
    m_type(btn_type),
    m_status(DEFAULT),
    m_hold_pos{0, 0},
    m_scrollbar(&scrollbar)
{
    // UniversalLayoutBox box(0_px, 0_px);
    // double scrollbar_thickness = scrollbar.getThickness();
    // box.setPosition(Vec2d(scrollbar_thickness, scrollbar_thickness));

    // setLayoutBox(box);
}

bool ScrollBar::ScrollButton::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = Button::onMousePressed(key, x, y, transf_list);

    if (res)
    {
        m_status = HOLD;

        // TODO: make more based and less cringe
        // for compatibility only
        Transform m_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());

        transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
        Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

        Vec2d pos = top_transf.restore(Vec2d(x, y));
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

    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (m_status == HOLD)
    {
        Vec2d delta_hold_pos = (pos - m_hold_pos) * top_transf.getScale();

        if (m_type == VER)
            delta_hold_pos.x = 0;
        else if (m_type == HOR)
            delta_hold_pos.y = 0;

        Vec2d delta_perc = delta_hold_pos / 
                          (m_scrollbar->getWrappeeSize() -
                           m_scrollbar->getVisibleAreaSize());

        m_scrollbar->deltaPercentageOffset(delta_perc);
    }

    transf_list.PopBack();

    return true;
}

// ==========================================

ScrollBar::ScrollBar(Widget &wrappee, const Length &thickness, const Length &width, const Length &height, scrollable_t type, ScrollBarTexture &texture) :
    Widget(UniversalLayoutBox(0_px, 0_px)),
    m_wrappee(&wrappee),
    m_thickness(thickness),
    m_wrappee_stolen_layout_box(wrappee.getLayoutBox().clone()),
    m_width(-1),
    m_height(-1),
    m_is_ver(type & SCROLLABLE_VERTICAL),
    m_is_hor(type & SCROLLABLE_HORIZONTAL),
    m_texture(&texture),
    m_btn_ver  (*this, VER,                *texture.m_btn_scroll),
    m_btn_hor  (*this, HOR,                *texture.m_btn_scroll),
    m_btn_up   (*this, Vec2d (   0, -0.1), *texture.m_btn_up),
    m_btn_down (*this, Vec2d (   0, +0.1), *texture.m_btn_down),
    m_btn_left (*this, Vec2d (-0.1,    0), *texture.m_btn_left),
    m_btn_right(*this, Vec2d (+0.1,    0), *texture.m_btn_right)
{
    Vec2d wrappee_pos  = wrappee.getLayoutBox().getPosition();
    Vec2d wrappee_size = wrappee.getLayoutBox().getSize();

    wrappee.setLayoutBox(UniversalLayoutBox(Length(wrappee_size.x, Unit::Pixel),
                                            Length(wrappee_size.y, Unit::Pixel)));

    Vec2d add_size(m_is_ver ? thickness : 0, m_is_hor ? thickness : 0);
    Vec2d whole_size = Vec2d(width, height) + add_size;
    onResize(whole_size.x, whole_size.y);

    setPercentageOffset(Vec2d(0, 0));
    getLayoutBox().setPosition(wrappee_pos);
}

Vec2d ScrollBar::getPercentageCovering() const
{
    Vec2d own_size(m_width, m_height);
    Vec2d wrappee_size = m_wrappee->getLayoutBox().getSize();

    return Vec2d(clip(own_size.x / wrappee_size.x),
                 clip(own_size.y / wrappee_size.y));
}

Vec2d ScrollBar::getPercentageOffset() const
{
    return Vec2d(m_hor_per, m_ver_per);
}

void ScrollBar::setPercentageOffset(const Vec2d &perc)
{
    Vec2d perc_offset = getPercentageOffset();
    deltaPercentageOffset(perc - perc_offset);
}

void ScrollBar::deltaPercentageOffset(const Vec2d &delta)
{
    Vec2d perc_offset = getPercentageOffset();
    perc_offset += delta;

    m_hor_per = perc_offset.x = clip(perc_offset.x);
    m_ver_per = perc_offset.y = clip(perc_offset.y);

    updateComponentsPositionsByPercents();
}

Vec2d ScrollBar::getPrefferedButtonsSizes() const
{
    Vec2d perc_cov = getPercentageCovering();
    Vec2d own_size(m_width, m_height);
    Vec2d buttons_sizes = (own_size - 2 * Vec2d(m_thickness, m_thickness)) * perc_cov;

    buttons_sizes.x = std::min(buttons_sizes.x, 0.5 * own_size.x);
    buttons_sizes.y = std::min(buttons_sizes.y, 0.5 * own_size.y);

    return buttons_sizes;
}

void ScrollBar::updateButtonsSizes()
{
    Vec2d pref_btns_sizes = getPrefferedButtonsSizes();

    m_btn_ver.getLayoutBox().setSize(Vec2d(m_thickness, pref_btns_sizes.y));
    m_btn_hor.getLayoutBox().setSize(Vec2d(pref_btns_sizes.x, m_thickness));

    for (ScrollDeltaButton *delta_btn : {&m_btn_up, &m_btn_down, &m_btn_left, &m_btn_right})
        delta_btn->getLayoutBox().setSize(Vec2d(m_thickness, m_thickness));
}

void ScrollBar::updateComponentsPositionsByPercents()
{
    Vec2d perc_offset(m_hor_per, m_ver_per);
    Vec2d pref_btns_sizes = getPrefferedButtonsSizes();

    // scroll button position
    LayoutBox &btn_ver_box = m_btn_ver.getLayoutBox();
    double prev_pos_y = perc_offset.y * (m_height - pref_btns_sizes.y - 2 * m_thickness);
    btn_ver_box.setPosition(Vec2d(m_width, m_thickness + prev_pos_y));

    LayoutBox &btn_hor_box = m_btn_hor.getLayoutBox();
    double prev_pos_x = perc_offset.x * (m_width - pref_btns_sizes.x - 2 * m_thickness);
    btn_hor_box.setPosition(Vec2d(m_thickness + prev_pos_x, m_height));

    // delta button position
    m_btn_up   .getLayoutBox().setPosition(Vec2d(m_width, 0));
    m_btn_down .getLayoutBox().setPosition(Vec2d(m_width, m_height - m_thickness));
    m_btn_left .getLayoutBox().setPosition(Vec2d(0, m_height));
    m_btn_right.getLayoutBox().setPosition(Vec2d(m_width - m_thickness, m_height));

    // wrappee fake position
    Vec2d wrappee_size = m_wrappee->getLayoutBox().getSize();
    Vec2d own_size(m_width, m_height);
    m_wrappee->getLayoutBox().setPosition(-perc_offset * (wrappee_size - own_size));
}

double ScrollBar::clip(double perc)
{
    return std::min(1., std::max(0., perc));
}

double ScrollBar::getThickness() const
{
    return m_thickness;
}

Vec2d ScrollBar::getVisibleAreaSize() const
{
    return Vec2d(m_width, m_height);
}

Vec2d ScrollBar::getWrappeeSize() const
{
    return m_wrappee->getLayoutBox().getSize();
}

void ScrollBar::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    sf::RenderTexture fake_target;
    fake_target.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    m_wrappee->draw(fake_target, transf_list);
    fake_target.display();

    sf::VertexArray vertex_arr(sf::Quads, 4);

    vertex_arr[0].position = vertex_arr[0].texCoords = {0, 0};
    vertex_arr[1].position = vertex_arr[1].texCoords = {m_width, 0};
    vertex_arr[2].position = vertex_arr[2].texCoords = {m_width, m_height};
    vertex_arr[3].position = vertex_arr[3].texCoords = {0, m_height};

    for (int32_t i = 0; i < 4; ++i)
    {
        vertex_arr[i].position  = static_cast<Vector2f>(top_transf.apply(static_cast<Vec2d>(vertex_arr[i].position)));
        vertex_arr[i].texCoords = static_cast<Vector2f>(top_transf.apply(static_cast<Vec2d>(vertex_arr[i].texCoords)));
    }

    target.draw(vertex_arr, &fake_target.getTexture());

    if (m_is_ver)
    {
        m_btn_ver .draw(target, transf_list);
        m_btn_up  .draw(target, transf_list);
        m_btn_down.draw(target, transf_list);
    }

    if (m_is_hor)
    {
        m_btn_hor  .draw(target, transf_list);
        m_btn_left .draw(target, transf_list);
        m_btn_right.draw(target, transf_list);
    }

    transf_list.PopBack();
}

bool ScrollBar::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = false;
    
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (m_is_ver)
    {
        res = res || m_btn_ver .onMousePressed(key, x, y, transf_list);
        res = res || m_btn_up  .onMousePressed(key, x, y, transf_list);
        res = res || m_btn_down.onMousePressed(key, x, y, transf_list);
    }

    if (m_is_hor)
    {
        res = res || m_btn_hor  .onMousePressed(key, x, y, transf_list);
        res = res || m_btn_left .onMousePressed(key, x, y, transf_list);
        res = res || m_btn_right.onMousePressed(key, x, y, transf_list);
    }

    if (res)
    {
        transf_list.PopBack();
        return true;
    }

    if (EPS < pos.x && pos.x < m_width - EPS &&
        EPS < pos.y && pos.y < m_height - EPS)
        res = res || m_wrappee->onMousePressed(key, x, y, transf_list);

    transf_list.PopBack();
    return res;
}

bool ScrollBar::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    m_wrappee->onMouseReleased(key, x, y, transf_list);

    if (m_is_ver)
    {
        m_btn_ver .onMouseReleased(key, x, y, transf_list);
        m_btn_up  .onMouseReleased(key, x, y, transf_list);
        m_btn_down.onMouseReleased(key, x, y, transf_list);
    }
    if (m_is_hor)
    {
        m_btn_hor  .onMouseReleased(key, x, y, transf_list);
        m_btn_left .onMouseReleased(key, x, y, transf_list);
        m_btn_right.onMouseReleased(key, x, y, transf_list);
    }

    transf_list.PopBack();
}

bool ScrollBar::onResize(float width, float height)
{
    Vec2d prev_visible_area_size = Vec2d(m_width, m_height);

    m_width  = std::max(m_thickness, width  - (m_is_ver ? m_thickness : 0));
    m_height = std::max(m_thickness, height - (m_is_hor ? m_thickness : 0));

    if (prev_visible_area_size == Vec2d(m_width, m_height))
        return false;

    getLayoutBox().setSize(Vec2d(width, height));
    m_btn_ver.onParentUpdate(getLayoutBox());
    m_btn_hor.onParentUpdate(getLayoutBox());
    updateButtonsSizes();
    updateComponentsPositionsByPercents();
    
    return true;
}

bool ScrollBar::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    m_wrappee->onMouseMoved(x, y, transf_list);

    if (m_is_ver)
    {
        m_btn_ver .onMouseMoved(x, y, transf_list);
        m_btn_up  .onMouseMoved(x, y, transf_list);
        m_btn_down.onMouseMoved(x, y, transf_list);
    }

    if (m_is_hor)
    {
        m_btn_hor  .onMouseMoved(x, y, transf_list);
        m_btn_left .onMouseMoved(x, y, transf_list);
        m_btn_right.onMouseMoved(x, y, transf_list);
    }

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

