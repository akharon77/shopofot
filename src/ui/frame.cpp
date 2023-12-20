#include <cstdio>

#include "ui/frame.hpp"
#include "math/transform_stack.hpp"
#include "graphics/shapes.hpp"

static const double EPS = 1e-6;
static TransformStack FAKE_STACK;
static plug::EHC FAKE_EHC((plug::TransformStack&) FAKE_STACK, false, false);

Frame::Frame(Widget &wrappee, const char *title, double thickness, FrameTexture &frame_texture) :
    Widget(UniversalLayoutBox(0_px, 0_px)),
    m_wrappee(&wrappee),
    m_title(title),
    m_thickness(thickness),
    m_wrappee_stolen_layout_box(wrappee.getLayoutBox().clone()),
    m_vertex_array(plug::PrimitiveType::Quads, 4),
    m_status(status_t::DEFAULT),
    m_frame_texture(&frame_texture),
    m_close_btn(*frame_texture.m_close_btn_texture),
    m_interactive(interactive_t::DEFAULT)
{
    plug::Vec2d wrappee_pos  = wrappee.getLayoutBox().getPosition();
    plug::Vec2d wrappee_size = wrappee.getLayoutBox().getSize();

    getLayoutBox().setPosition(wrappee_pos);
    getLayoutBox().setSize(wrappee_size + plug::Vec2d(thickness, thickness) * 2);

    UniversalLayoutBox *new_wrappee_box = new UniversalLayoutBox(0_px, 0_px);
    new_wrappee_box->setSize(wrappee_size);
    new_wrappee_box->setAlignment(Align::Center);
    new_wrappee_box->onParentUpdate(getLayoutBox());
    wrappee.setLayoutBox(*new_wrappee_box);

    updateVertexArray();

    FAKE_EHC.stopped = false;
    m_close_btn.onResize(thickness, thickness, FAKE_EHC);
    m_close_btn.getLayoutBox().setPosition(plug::Vec2d(wrappee_size.x + thickness, 0));
}

void Frame::updateVertexArray()
{
    plug::Vec2d size = getLayoutBox().getSize();

    m_vertex_array[0].position = plug::Vec2d(0,      0);
    m_vertex_array[1].position = plug::Vec2d(size.x, 0);
    m_vertex_array[2].position = plug::Vec2d(size.x, size.y);
    m_vertex_array[3].position = plug::Vec2d(0,      size.y);
}

void Frame::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    stack.enter(own_transf);

    plug::VertexArray buf_vertex_array(m_vertex_array);
    for (int32_t i = 0; i < buf_vertex_array.getSize(); ++i)
    {
        plug::Vec2d pos = stack.apply(m_vertex_array[i].position);
        buf_vertex_array[i].position = pos;
    }

    target.draw(buf_vertex_array);
    m_wrappee->draw(stack, target);

    Vec2d pos = stack.apply(Vec2d(0, 0));
    pos += Vec2d(m_thickness * 0.05, m_thickness * 0.05);

    sf::Text text;
    text.setFont(m_frame_texture->font);
    text.setString(m_title);
    text.setCharacterSize(m_thickness * 0.9);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos.x, pos.y);
    target.getSFMLRenderTarget().draw(text);

    // drawText(target, , m_title, m_thickness * 0.9, plug::Color(235, 101, 135));

    if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
        m_close_btn.draw(stack, target);

    stack.leave();
}

void Frame::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
    {
        m_close_btn.onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
        if (context.stopped)
        {
            context.stack.leave();
            return;
        }
    }

    plug::Vec2d pos = context.stack.restore(plug::Vec2d(x, y));
    // cringe for compatibility only
    plug::Vec2d m_size = getLayoutBox().getSize();

    if (EPS < pos.x && pos.x < m_size.x    - EPS &&
        EPS < pos.y && pos.y < m_thickness - EPS)
    {
        m_status = status_t::HOLD;
        m_hold_pos = pos;

        context.stopped = true;
        printf("hold\n");
        printf("size: %lf, %lf\n", getLayoutBox().getSize().x, getLayoutBox().getSize().y);
    }

    if (EPS + m_wrappee->getLayoutBox().getSize().x + m_thickness < pos.x && pos.x < m_size.x - EPS &&
        EPS + m_thickness < pos.y && pos.y < m_size.y - EPS)
    {
        m_status = (status_t) ((uint8_t) m_status | (uint8_t) status_t::HOLD_HOR);
        m_hold_pos = pos;

        context.stopped = true;
        printf("hold hor\n");
    }

    if (EPS + m_thickness < pos.x && pos.x < m_size.x - EPS &&
        EPS + m_thickness + m_wrappee->getLayoutBox().getSize().y  < pos.y && pos.y < m_size.y)
    {
        m_status = (status_t) ((uint8_t) m_status | (uint8_t) status_t::HOLD_VER);
        m_hold_pos = pos;

        context.stopped = true;
        printf("hold ver\n");
    }

    m_wrappee->onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);

    context.stack.leave();
}

void Frame::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
    {
        m_close_btn.onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
        if (context.stopped)
        {
            context.stack.leave();
            return;
        }
    }

    plug::Vec2d pos = context.stack.restore(plug::Vec2d(x, y));

    if (m_status != status_t::DEFAULT)
    {
        m_status = status_t::DEFAULT;

        context.stopped = true;
        context.stack.leave();
        return;
    }

    m_wrappee->onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);

    context.stack.leave();
}

void Frame::onResize(double width, double height, plug::EHC &context)
{
    m_wrappee->onEvent((const plug::Event&) ResizeEvent(Vec2d(width, height) - Vec2d(m_thickness, m_thickness) * 2), context);
    if (!context.stopped)
        return;

    getLayoutBox().setSize(plug::Vec2d(width, height));
    m_wrappee->getLayoutBox().onParentUpdate(getLayoutBox());
    m_close_btn.getLayoutBox().setPosition(plug::Vec2d(width - m_thickness, 0));
    updateVertexArray();
}

void Frame::onMouseMoved(double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);
    
    if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
    {
        m_close_btn.onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
        if (context.overlapped)
        {
            context.stack.leave();
            return;
        }
    }

    plug::Vec2d pos = context.stack.restore(plug::Vec2d(x, y));

    if (m_status == status_t::HOLD)
    {
        plug::Vec2d delta_hold_pos = pos - m_hold_pos;
        plug::Vec2d new_pos = getLayoutBox().getPosition() + delta_hold_pos * context.stack.top().getScale();
        getLayoutBox().setPosition(new_pos);
        context.stopped = true;
    }

    if ((uint8_t) m_status & (uint8_t) status_t::HOLD_HOR)
    {
        plug::Vec2d delta_hold_pos = pos - m_hold_pos;
        FAKE_EHC.stopped = false;
        onResize(getLayoutBox().getSize().x + delta_hold_pos.x * context.stack.top().getScale().x, getLayoutBox().getSize().y, FAKE_EHC);
        m_hold_pos.x = getLayoutBox().getSize().x;
        context.stopped = true;
    }

    if ((uint8_t) m_status & (uint8_t) status_t::HOLD_VER)
    {
        plug::Vec2d delta_hold_pos = pos - m_hold_pos;
        FAKE_EHC.stopped = false;
        onResize(getLayoutBox().getSize().x, getLayoutBox().getSize().y + delta_hold_pos.y * context.stack.top().getScale().y, FAKE_EHC);
        m_hold_pos.y = getLayoutBox().getSize().y;
        context.stopped = true;
    }

    m_wrappee->onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
    context.stack.leave();
}

void Frame::onKeyboardPressed(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    m_wrappee->onEvent((const plug::Event&) plug::KeyboardPressedEvent(key, false, false, false), context);
}

void Frame::onKeyboardReleased(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    m_wrappee->onEvent((const plug::Event&) plug::KeyboardReleasedEvent(key, false, false, false), context);
}

void Frame::onTime(double d_seconds, plug::EHC &context)
{
    if (context.stopped)
        return;

    m_wrappee->onEvent((const plug::Event&) plug::TickEvent(d_seconds), context);
}

void Frame::setClosable(bool flag)
{
    if (flag)
        m_interactive = (interactive_t) ((uint8_t) m_interactive | (uint8_t) interactive_t::CLOSABLE);
    else
        m_interactive = (interactive_t) ((uint8_t) m_interactive & ~((uint8_t) interactive_t::CLOSABLE));
}

void Frame::CloseButton::setContainer(Container &container)
{
    m_container = &container;
}

void Frame::CloseButton::setCloseId(int32_t id)
{
    m_close_id = id;
}

void Frame::setContainer(Container &container)
{
    m_close_btn.setContainer(container);
}

void Frame::setCloseId(int32_t id)
{
    m_close_btn.setCloseId(id);
}

void Frame::CloseButton::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Button::onMousePressed(key, x, y, context);

    if (context.stopped)
        m_container->close(m_close_id);
}

