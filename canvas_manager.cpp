#include "canvas_manager.hpp"

CanvasManager::CanvasManager(Vector2f pos, Vector2f size, ToolPalette &tool_palette, FilterPalette &filter_palette, CanvasManagerTexture &canv_manager_texture) :
    Widget(Transform{pos, Vector2f{1, 1}}, size),
    m_tool_palette(&tool_palette),
    m_filter_palette(&filter_palette),
    m_texture(&canv_manager_texture)
{}

void CanvasManager::addCanvas(int32_t canv_width, int32_t canv_height)
{
    Canvas *canvas = new Canvas(m_size / 2.f, m_size.x, m_size.y, canv_width, canv_height, *m_tool_palette, *m_filter_palette);
    ScrollBar *scrollbar = new ScrollBar(*canvas, 0.01, 0.3, true, 0.3, true, *m_texture->m_scrollbar_texture);
    Frame *frame = new Frame(*scrollbar, "hello", 0.02, *m_texture->m_frame_texture);
    
    // sf::Image cat_img;
    // cat_img.loadFromFile("cat.jpg");

    // canvas->loadFromImage(cat_img);

    int32_t id = m_canv_window_lst.PushFront(new CanvasWindow(canvas, scrollbar, frame));
    frame->setClosable(true);
    frame->setContainer(*this);
    frame->setCloseId(id);
}

CanvasManager::CanvasWindow::~CanvasWindow()
{
    delete m_canvas;
    delete m_scrollbar;
    delete m_frame;
}

bool CanvasManager::close(int32_t id)
{
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(id);
    delete node.val;
    m_canv_window_lst.Erase(id);
}

void CanvasManager::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_canv_window_lst.GetTail();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->m_frame->draw(target, transf_list);
        anch = node.prev;
        node = *m_canv_window_lst.Get(anch);
    }

    transf_list.PopBack();
}

bool CanvasManager::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        bool res = node.val->m_frame->onMousePressed(key, x, y, transf_list);
        if (res)
        {
            if (m_canv_window_lst.GetSize() == size)
            {
                CanvasWindow *val = node.val;
                m_canv_window_lst.Erase(anch);
                m_canv_window_lst.PushFront(val);
            }

            transf_list.PopBack();
            return true;
        }

        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }

    transf_list.PopBack();
    return false;
};

bool CanvasManager::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        bool res = node.val->m_frame->onMouseReleased(key, x, y, transf_list);
        if (res)
        {
            CanvasWindow *val = node.val;
            m_canv_window_lst.Erase(anch);
            m_canv_window_lst.PushFront(val);

            transf_list.PopBack();
            return true;
        }

        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }

    transf_list.PopBack();
    return false;
};

bool CanvasManager::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        bool res = node.val->m_frame->onMouseMoved(x, y, transf_list);
        if (res)
        {
            CanvasWindow *val = node.val;
            m_canv_window_lst.Erase(anch);
            m_canv_window_lst.PushFront(val);

            transf_list.PopBack();
            return true;
        }

        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }

    transf_list.PopBack();
    return false;
};

bool CanvasManager::onKeyboardPressed(KeyboardKey key)
{
    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    return node.val->m_frame->onKeyboardPressed(key);
}

bool CanvasManager::onKeyboardReleased(KeyboardKey key)
{
    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    return node.val->m_frame->onKeyboardReleased(key);
}

bool CanvasManager::onTime(float d_seconds)
{
    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);

    int32_t size = m_canv_window_lst.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->m_frame->onTime(d_seconds);
        anch = node.next;
        node = *m_canv_window_lst.Get(anch);
    }

    return true;
}

bool CanvasManager::onResize(float width, float height)
{
    return false;
}

Canvas *CanvasManager::getActive()
{
    int32_t anch = m_canv_window_lst.GetHead();
    Node<CanvasWindow*> node = *m_canv_window_lst.Get(anch);
    return node.val->m_canvas;
}

FilterPalette *CanvasManager::getFilterPalette()
{
    return m_filter_palette;
}

ToolPalette *CanvasManager::getToolPalette()
{
    return m_tool_palette;
}

