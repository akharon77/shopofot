#include "ui/canvas_view.hpp"
#include "util/sfml.hpp"
#include "plug/tool.hpp"
#include "math/transform_stack.hpp"

static const double EPS = 1e-6;

CanvasView::CanvasView(const plug::LayoutBox &box, int32_t canv_width, int32_t canv_height, ToolPalette &tool_palette, FilterPalette &filter_palette, plug::ColorPalette &color_palette) :
    Widget(box),
    m_canvas(new Canvas(canv_width, canv_height, getPlugColor(sf::Color::Transparent))),
    m_tool_palette(&tool_palette),
    m_filter_palette(&filter_palette),
    m_color_palette(&color_palette),
    m_last_mouse_pos(0, 0),
    m_active(false)
{}

void CanvasView::loadFromImage(const char *path)
{
    delete m_canvas;
    m_canvas = new Canvas(path);
}

void CanvasView::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    stack.enter(own_transf);

    Vec2d size = m_canvas->getSize();
    plug::VertexArray buf_vertex_arr(plug::PrimitiveType::Quads, 4);

    buf_vertex_arr[0].tex_coords = Vec2d(0, 0);
    buf_vertex_arr[1].tex_coords = Vec2d(size.x, 0);
    buf_vertex_arr[2].tex_coords = Vec2d(size.x, size.y);
    buf_vertex_arr[3].tex_coords = Vec2d(0, size.y);

    buf_vertex_arr[0].position = Vec2d(0, 0);
    buf_vertex_arr[1].position = Vec2d(1, 0);
    buf_vertex_arr[2].position = Vec2d(1, 1);
    buf_vertex_arr[3].position = Vec2d(0, 1);

    for (int32_t i = 0; i < 4; ++i)
        buf_vertex_arr[i].position = stack.apply(buf_vertex_arr[i].position);

    target.draw(buf_vertex_arr, m_canvas->getTexture());

    if (m_active)
    {
        plug::Tool *tool = m_tool_palette->getActiveTool();
        if (tool != nullptr)
        {
            plug::Widget *tool_widget = tool->getWidget();
            if (tool_widget != nullptr)
            {
                stack.enter(Transform(Vec2d(0, 0), Vec2d(1, 1) / m_canvas->getSize()));
                tool_widget->draw(stack, target);
                stack.leave();
            }
        }
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
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));
    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        plug::Tool *tool = m_tool_palette->getActiveTool();
        if (tool != nullptr)
        {
            tool->setActiveCanvas(*m_canvas);
            tool->setColorPalette(*m_color_palette);
            tool->onMainButton(plug::ControlState(plug::State::Pressed),
                    pos * m_canvas->getSize());

            plug::Widget *tool_widget = tool->getWidget();
            if (tool_widget != nullptr)
                tool_widget->onEvent((const plug::Event&)
                        plug::MousePressedEvent(key, Vec2d(x, y), false, false, false), 
                        context);
        }

        context.stack.leave();
        context.stopped = true;
        return; 
    }

    context.stack.leave();
}

void CanvasView::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    plug::Tool *tool = m_tool_palette->getActiveTool();
    if (tool != nullptr)
    {
        plug::Vec2d pos = context.stack.restore(Vec2d(x, y));
        tool->onMainButton(plug::ControlState(plug::State::Released),
                    pos * m_canvas->getSize());

        plug::Widget *tool_widget = tool->getWidget();
        if (tool_widget != nullptr)
            tool_widget->onEvent((const plug::Event&)
                plug::MouseReleasedEvent(key, Vec2d(x, y), false, false, false),
                context);
    }

    context.stack.leave();
}

void CanvasView::onMouseMoved(double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    if (context.overlapped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());
    context.stack.enter(own_transf);

    Vec2d pos = context.stack.restore(Vec2d(x, y));
    m_last_mouse_pos = pos;

    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
        context.overlapped = true;

    plug::Tool *tool = m_tool_palette->getActiveTool();
    if (tool != nullptr)
    {
        tool->onMove(pos * m_canvas->getSize());

        plug::Widget *tool_widget = tool->getWidget();
        if (tool_widget != nullptr)
            tool_widget->onEvent((const plug::Event&)
                    plug::MouseMoveEvent(Vec2d(x, y), false, false, false),
                    context);
    }

    context.stack.leave();
}

void CanvasView::onKeyboardPressed(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Tool *tool = m_tool_palette->getActiveTool();
    if (tool != nullptr)
    {
        plug::Widget *tool_widget = tool->getWidget();

        if (tool_widget != nullptr)
        {
            if (key == plug::KeyCode::Enter)
            {
                m_tool_palette->getActiveTool()->onConfirm();
                context.stopped = true;
                return;
            }

            if (key == plug::KeyCode::Escape)
            {
                m_tool_palette->getActiveTool()->onCancel();
                context.stopped = true;
                return;
            }
        }

        if (key == plug::KeyCode::Right)
        {
            m_tool_palette->nextTool();
            context.stopped = true;
            return;
        }

        if (key == plug::KeyCode::Left)
        {
            m_filter_palette->nextFilter();
            context.stopped = true;
            return;
        }


        if (tool_widget != nullptr)
            tool_widget->onEvent((const plug::Event&)
                    plug::KeyboardPressedEvent(key, false, false, false),
                    context);

    }

    if (key == plug::KeyCode::F)
    {
        m_filter_palette->getLastFilter()->applyFilter(*m_canvas);
        context.stopped = true;
        return;
    }
}

void CanvasView::onKeyboardReleased(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Tool *tool = m_tool_palette->getActiveTool();
    if (tool == nullptr)
        return;

    plug::Widget *tool_widget = tool->getWidget();
    if (tool_widget != nullptr)
        tool_widget->onEvent((const plug::Event&)
                plug::KeyboardReleasedEvent(key, false, false, false),
                context);
}

void CanvasView::onTime(double d_seconds, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Tool *tool = m_tool_palette->getActiveTool();
    if (tool == nullptr)
        return;

    plug::Widget *tool_widget = tool->getWidget();
    if (tool_widget != nullptr)
        tool_widget->onEvent((const plug::Event&)
                plug::TickEvent(d_seconds), context);
}

