#include "ui/canvas_view_manager.hpp"
#include "universal_layoutbox.hpp"
#include "math/transform_stack.hpp"

CanvasViewManager::CanvasViewManager(const plug::LayoutBox &box, ToolPalette &tool_palette, FilterPalette &filter_palette, CanvasViewManagerTexture &canv_manager_texture) :
    Widget(box),
    m_tool_palette(&tool_palette),
    m_filter_palette(&filter_palette),
    m_texture(&canv_manager_texture)
{}

void CanvasViewManager::addCanvas(int32_t canv_width, int32_t canv_height)
{
    Vec2d own_size = getLayoutBox().getSize();

    UniversalLayoutBox canv_base_box(0_px, 0_px);
    canv_base_box.setSize(own_size);
    canv_base_box.setPosition(own_size / 2);

    CanvasView *canvas    = new CanvasView(canv_base_box, canv_width, canv_height, *m_tool_palette, *m_filter_palette);
    ScrollBar *scrollbar = new ScrollBar(*canvas, 1_cm, 10_cm, 10_cm, static_cast<ScrollBar::scrollable_t>(ScrollBar::SCROLLABLE_VERTICAL | ScrollBar::SCROLLABLE_HORIZONTAL), *m_texture->m_scrollbar_texture);
    Frame     *frame     = new Frame(*scrollbar, "hello", 8_mm, *m_texture->m_frame_texture);

    canvas->loadFromImage("assets/img/cat.jpg");

    int32_t id = m_canv_window_lst.PushFront(new CanvasWindow(canvas, scrollbar, frame));
    frame->setClosable(true);
    frame->setContainer(*this);
    frame->setCloseId(id);
}

CanvasViewManager::CanvasWindow::~CanvasWindow()
{
    delete m_canvas;
    delete m_scrollbar;
    delete m_frame;
}

bool CanvasViewManager::close(int32_t id)
{
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(id);
    delete node.val;
    m_canv_window_lst.Erase(id);
}

void CanvasViewManager::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    stack.enter(own_transf);

    int32_t anch = m_canv_window_lst.GetTail();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->m_frame->draw(stack, target);
        anch = node.prev;
        node = *m_canv_window_lst.Get(anch);
    }

    stack.leave();
}

void CanvasViewManager::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->m_frame->onMousePressed(key, x, y, context);
        if (context.stopped)
        {
            if (m_canv_window_lst.GetSize() == size)
            {
                CanvasWindow *val = node.val;
                m_canv_window_lst.Erase(anch);
                m_canv_window_lst.PushFront(val);
            }

            context.stack.leave();
            return;
        }

        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }

    context.stack.leave();
};

void CanvasViewManager::onMouseReleased(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->m_frame->onMouseReleased(key, x, y, context);
        if (context.stopped)
        {
            CanvasWindow *val = node.val;
            m_canv_window_lst.Erase(anch);
            m_canv_window_lst.PushFront(val);

            context.stack.leave();
            return;
        }

        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }

    context.stack.leave();
}

void CanvasViewManager::onMouseMoved(double x, double y, plug::EHC &context)
{
    if (context.stopped)
        return;

    plug::Transform own_transf(getLayoutBox().getPosition(), plug::Vec2d(1, 1));
    context.stack.enter(own_transf);
    
    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->m_frame->onMouseMoved(x, y, context);
        if (context.stopped)
        {
            CanvasWindow *val = node.val;
            m_canv_window_lst.Erase(anch);
            m_canv_window_lst.PushFront(val);

            context.stack.leave();
            return;
        }

        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }

    context.stack.leave();
}

void CanvasViewManager::onKeyboardPressed(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    node.val->m_frame->onKeyboardPressed(key, context);
}

void CanvasViewManager::onKeyboardReleased(plug::KeyCode key, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    node.val->m_frame->onKeyboardReleased(key, context);
}

void CanvasViewManager::onTime(double d_seconds, plug::EHC &context)
{
    if (context.stopped)
        return;

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->m_frame->onTime(d_seconds, context);
        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }
}

void CanvasViewManager::onResize(double width, double height, plug::EHC &context)
{
    context.stopped = false;
}

CanvasView *CanvasViewManager::getActive()
{
    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);
    return node.val->m_canvas;
}

FilterPalette *CanvasViewManager::getFilterPalette()
{
    return m_filter_palette;
}

ToolPalette *CanvasViewManager::getToolPalette()
{
    return m_tool_palette;
}

