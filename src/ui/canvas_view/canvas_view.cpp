#include "ui/canvas_view.hpp"
#include "util/sfml.hpp"

static const double EPS = 1e-6;

CanvasView::CanvasView(const plug::LayoutBox &box, int32_t canv_width, int32_t canv_height, ToolPalette &tool_palette, FilterPalette &filter_palette) :
    Widget(box),
    m_vertex_arr(plug::PrimitiveType::Quads, 4),
    m_canv_width(canv_width),
    m_canv_height(canv_height),
    m_tool_palette(&tool_palette),
    m_filter_mask(canv_width, canv_height),
    m_filter_palette(&filter_palette),
    m_canv_texture(m_sf_canv_texture, canv_width, canv_height),
    m_last_mouse_pos(0, 0)
{
    m_canv_texture.create(canv_width, canv_height);
    m_canv_texture.clear(getPlugColor(sf::Color::Black));

    m_vertex_arr[0].position = plug::Vec2d(0, 0);
    m_vertex_arr[1].position = plug::Vec2d(1, 0);
    m_vertex_arr[2].position = plug::Vec2d(1, 1);
    m_vertex_arr[3].position = plug::Vec2d(0, 1);
    
    updateVertexArray();
}

void CanvasView::updateVertexArray()
{
    m_vertex_arr[0].tex_coords = Vec2d(0, 0);
    m_vertex_arr[1].tex_coords = Vec2d(m_canv_width, 0);
    m_vertex_arr[2].tex_coords = Vec2d(m_canv_width, m_canv_height);
    m_vertex_arr[3].tex_coords = Vec2d(0, m_canv_height);
}

// sf::Image CanvasView::getImage()
// {
//     return m_canv_texture.getTexture().copyToImage();
// }

// void CanvasView::drawImage(const sf::Image &image)
// {
//     sf::Texture buf_texture;
//     buf_texture.loadFromImage(image);
// 
//     sf::Sprite buf_sprite;
//     buf_sprite.setTexture(buf_texture);
//     m_canv_texture.draw(buf_sprite);
//     m_canv_texture.display();
// }

// void CanvasView::loadFromImage(const sf::Image &image)
// {
//     sf::Vector2u size = image.getSize();
//     resize(size.x, size.y);
//     drawImage(image);
// }

void CanvasView::resize(uint32_t width, uint32_t height)
{
    m_canv_width = width;
    m_canv_height = height;
    updateVertexArray();

    m_filter_mask.resize(width, height);

    m_canv_texture.create(width, height);
}

void CanvasView::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    stack.enter(own_transf);

    plug::VertexArray buf_vertex_arr(m_vertex_arr);
    for (int32_t i = 0; i < 4; ++i)
        buf_vertex_arr[i].position = stack.apply(buf_vertex_arr[i].position);

    // m_canv_texture.display();
    target.draw(buf_vertex_arr, m_canv_texture.getPlugTexture());

    Tool *tool = m_tool_palette->getActiveTool();
    if (tool != nullptr)
    {
        Widget *tool_widget = tool->getWidget();
        if (tool_widget != nullptr)
            tool_widget->draw(stack, target);
    }

    stack.leave();
}

void CanvasView::onResize(double width, double height, plug::EHC &context)
{
    bool res = getLayoutBox().setSize(Vec2d(width, height));
    if (res)
        context.stopped = true;
}

void CanvasView::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context) 
{
    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));
    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        Tool *tool = m_tool_palette->getActiveTool();
        if (tool != nullptr)
        {
            tool->onMainButton(MouseType::PRESSED, pos, *this);

            Widget *tool_widget = tool->getWidget();
            if (tool_widget != nullptr)
                tool_widget->onEvent((const plug::Event&) plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), context);
        }

        context.stack.leave();
        context.stopped = true;
        return; 
    }

    context.stack.leave();
}

void CanvasView::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    Tool *tool = m_tool_palette->getActiveTool();
    if (tool != nullptr)
    {
        Vec2d pos = context.stack.restore(Vec2d(x, y));
        tool->onMainButton(MouseType::RELEASED, pos, *this);

        Widget *tool_widget = tool->getWidget();
        if (tool_widget != nullptr)
            tool_widget->onEvent((const plug::Event&) plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false), context);
    }

    context.stack.leave();
}

void CanvasView::onMouseMoved(double x, double y, plug::EHC &context)
{
    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));
    m_last_mouse_pos = pos;

    Tool *tool = m_tool_palette->getActiveTool();
    if (tool != nullptr)
    {
        tool->onMove(pos, *this);

        Widget *tool_widget = tool->getWidget();
        if (tool_widget != nullptr)
            tool_widget->onEvent((const plug::Event&) plug::MouseMoveEvent(Vec2d(x, y), false, false, false), context);
    }

    context.stack.leave();
}

void CanvasView::onKeyboardPressed(plug::KeyCode key, plug::EHC &context)
{
    Tool *tool = m_tool_palette->getActiveTool();
    if (tool == nullptr)
        return;

    Widget *tool_widget = tool->getWidget();

    if (key == plug::KeyCode::Right)
    {
        m_tool_palette->nextTool();
        context.stopped = true;
        return;
    }

    if (key == plug::KeyCode::Enter)
    {
        m_tool_palette->getActiveTool()->onConfirm(m_last_mouse_pos, *this);
        context.stopped = true;
        return;
    }

    if (key == plug::KeyCode::Escape)
    {
        m_tool_palette->getActiveTool()->onCancel(m_last_mouse_pos, *this);
        context.stopped = true;
        return;
    }

    if (key == plug::KeyCode::F)
    {
        m_filter_palette->getLastFilter()->applyFilter(*this, m_filter_mask);
        context.stopped = true;
        return;
    }

    if (tool_widget != nullptr)
        tool_widget->onEvent((const plug::Event&) plug::KeyboardPressedEvent(key, false, false, false), context);
}

void CanvasView::onKeyboardReleased(plug::KeyCode key, plug::EHC &context)
{
    Tool *tool = m_tool_palette->getActiveTool();
    if (tool == nullptr)
        return;

    Widget *tool_widget = tool->getWidget();
    if (tool_widget != nullptr)
        tool_widget->onEvent((const plug::Event&) plug::KeyboardReleasedEvent(key, false, false, false), context);
}

void CanvasView::onTime(double d_seconds, plug::EHC &context)
{
    Tool *tool = m_tool_palette->getActiveTool();
    if (tool == nullptr)
        return;

    Widget *tool_widget = tool->getWidget();
    if (tool_widget != nullptr)
        tool_widget->onEvent((const plug::Event&) plug::TickEvent(d_seconds), context);
}

