#include <type_traits>
#include <cstdio>

#include "universal_layoutbox.hpp"
#include "ui/scrollbar.hpp"
#include "math/transform_stack.hpp"
#include "graphics.hpp"

static const double EPS = 1e-6;
static TransformStack FAKE_STACK;
static plug::EHC FAKE_EHC((plug::TransformStack&) FAKE_STACK, false, false);

ScrollBar::ScrollDeltaButton::ScrollDeltaButton(ScrollBar &scrollbar, const Vec2d &delta, ButtonTexture &btn_texture) :
    Button(UniversalLayoutBox(), btn_texture),
    m_delta(delta),
    m_scrollbar(scrollbar)
{}

void ScrollBar::ScrollDeltaButton::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Button::onMousePressed(key, x, y, context);
    if (context.stopped)
    {
        printf("delta %lf\n", m_delta.x);
        m_scrollbar.deltaPercentageOffset(m_delta);
    }
}

ScrollBar::ScrollButton::ScrollButton(ScrollBar &scrollbar, scroll_button_t btn_type, ButtonTexture &btn_texture) :
    Button(UniversalLayoutBox(), btn_texture),
    m_type(btn_type),
    m_status(DEFAULT),
    m_hold_pos(0, 0),
    m_scrollbar(&scrollbar)
{}

void ScrollBar::ScrollButton::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Button::onMousePressed(key, x, y, context);

    if (context.stopped)
    {
        m_status = HOLD;

        Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
        context.stack.enter(own_transf);

        Vec2d pos = context.stack.restore(Vec2d(x, y));
        m_hold_pos = pos;

        context.stack.leave();
    }
}

void ScrollBar::ScrollButton::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Button::onMouseReleased(key, x, y, context);
    m_status = DEFAULT;
}

void ScrollBar::ScrollButton::onMouseMoved(double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Button::onMouseMoved(x, y, context);

    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));

    if (m_status == HOLD)
    {
        Vec2d delta_hold_pos = (pos - m_hold_pos) * context.stack.top().getScale();

        if (m_type == VER)
            delta_hold_pos.x = 0;
        else if (m_type == HOR)
            delta_hold_pos.y = 0;

        Vec2d delta_perc = delta_hold_pos / 
                          (m_scrollbar->getWrappeeSize() -
                           m_scrollbar->getVisibleAreaSize());

        m_scrollbar->deltaPercentageOffset(delta_perc);
    }

    context.stack.leave();
}

// ==========================================

ScrollBar::ScrollBar(plug::Widget &wrappee, const Length &thickness, const Length &width, const Length &height, scrollable_t type, ScrollBarTexture &texture) :
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

    FAKE_EHC.stopped = false;
    onResize(whole_size.x, whole_size.y, FAKE_EHC);

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
    Vec2d buttons_sizes = (own_size - Vec2d(m_thickness, m_thickness) * 2) * perc_cov;

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
    plug::LayoutBox &btn_ver_box = m_btn_ver.getLayoutBox();
    double prev_pos_y = perc_offset.y * (m_height - pref_btns_sizes.y - 2 * m_thickness);
    btn_ver_box.setPosition(Vec2d(m_width, m_thickness + prev_pos_y));

    plug::LayoutBox &btn_hor_box = m_btn_hor.getLayoutBox();
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

void ScrollBar::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    stack.enter(own_transf);

    sf::RenderTexture fake_sf_target;
    RenderTexture fake_target(fake_sf_target, SCREEN_WIDTH, SCREEN_HEIGHT);

    m_wrappee->draw(stack, fake_target);

    plug::VertexArray vertex_arr(plug::PrimitiveType::Quads, 4);

    vertex_arr[0].position = vertex_arr[0].tex_coords = Vec2d{0, 0};
    vertex_arr[1].position = vertex_arr[1].tex_coords = Vec2d{m_width, 0};
    vertex_arr[2].position = vertex_arr[2].tex_coords = Vec2d{m_width, m_height};
    vertex_arr[3].position = vertex_arr[3].tex_coords = Vec2d{0, m_height};

    for (int32_t i = 0; i < 4; ++i)
    {
        vertex_arr[i].position  = stack.apply(vertex_arr[i].position);
        vertex_arr[i].tex_coords = stack.apply(vertex_arr[i].tex_coords);
    }

    target.draw(vertex_arr, fake_target.getPlugTexture());

    if (m_is_ver)
    {
        m_btn_ver .draw(stack, target);
        m_btn_up  .draw(stack, target);
        m_btn_down.draw(stack, target);
    }

    if (m_is_hor)
    {
        m_btn_hor  .draw(stack, target);
        m_btn_left .draw(stack, target);
        m_btn_right.draw(stack, target);
    }

    stack.leave();
}

void ScrollBar::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));

    if (m_is_ver)
    {
        m_btn_ver .onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_up  .onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_down.onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
    }

    if (m_is_hor)
    {
        m_btn_hor  .onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_left .onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_right.onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
    }

    if (context.stopped)
    {
        context.stack.leave();
        return;
    }

    if (EPS < pos.x && pos.x < m_width - EPS &&
        EPS < pos.y && pos.y < m_height - EPS)
        m_wrappee->onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);

    context.stack.leave();
}

void ScrollBar::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));

    if (m_is_ver)
    {
        m_btn_ver .onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_up  .onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_down.onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
    }
    if (m_is_hor)
    {
        m_btn_hor  .onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_left .onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
        m_btn_right.onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
    }

    m_wrappee->onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);

    context.stack.leave();
}

void ScrollBar::onResize(double width, double height, plug::EHC &context)
{
    Vec2d prev_visible_area_size = Vec2d(m_width, m_height);

    m_width  = std::max(m_thickness, width  - (m_is_ver ? m_thickness : 0));
    m_height = std::max(m_thickness, height - (m_is_hor ? m_thickness : 0));

    if (prev_visible_area_size == Vec2d(m_width, m_height))
    {
        context.stopped = false;
        return;
    }

    getLayoutBox().setSize(Vec2d(width, height));
    m_btn_ver.onParentUpdate(getLayoutBox());
    m_btn_hor.onParentUpdate(getLayoutBox());
    updateButtonsSizes();
    updateComponentsPositionsByPercents();
    
    context.stopped = true;
}

void ScrollBar::onMouseMoved(double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));

    if (m_is_ver)
    {
        m_btn_ver .onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
        m_btn_up  .onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
        m_btn_down.onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
    }

    if (m_is_hor)
    {
        m_btn_hor  .onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
        m_btn_left .onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
        m_btn_right.onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
    }

    m_wrappee->onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);

    context.stack.leave();
}

void ScrollBar::onKeyboardPressed(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    m_wrappee->onEvent((const plug::Event&) plug::KeyboardPressedEvent(key, false, false, false), context);
}

void ScrollBar::onKeyboardReleased(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    m_wrappee->onEvent((const plug::Event&) plug::KeyboardReleasedEvent(key, false, false, false), context);
}

void ScrollBar::onTime(double d_seconds, plug::EHC &context)
{
    if (context.stopped)
        return;

    m_wrappee->onEvent((const plug::Event&) plug::TickEvent(d_seconds), context);
}

