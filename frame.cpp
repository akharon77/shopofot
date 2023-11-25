#include "frame.hpp"
#include "universal_layout_box.hpp"

Frame::Frame(Widget &wrappee, const char *title, const Length &thickness, FrameTexture &frame_texture) :
    Widget(UniversalLayoutBox()),
    m_wrappee(&wrappee),
    m_title(title),
    m_thickness(thickness),
    m_wrappee_stolen_layout_box(wrappee.getLayoutBox().clone()),
    m_vertex_array(sf::Quads, 4),
    m_status(status_t::DEFAULT),
    m_frame_texture(&frame_texture),
    // m_close_btn(*frame_texture.m_close_btn_texture),
    m_interactive(interactive_t::DEFAULT)
{
    // TODO
    // There should be special frame layoutbox, which will rebroadcast resizing right way,
    // but now there is wrong solution
    
    Vec2d wrappee_pos  = wrappee.getLayoutBox().getPosition();
    Vec2d wrappee_size = wrappee.getLayoutBox().getSize();

    getLayoutBox().setPosition(wrappee_pos);
    getLayoutBox().setSize(wrappee_size + 2 * Vec2d(thickness, thickness));

    UniversalLayoutBox *new_wrappee_box = new UniversalLayoutBox(0_px, 0_px);
    new_wrappee_box->onParentUpdate(getLayoutBox());
    new_wrappee_box->setSize(wrappee_size);
    new_wrappee_box->setAlignment(Align::Center);
    new_wrappee_box->onParentUpdate(getLayoutBox());
    wrappee.setLayoutBox(*new_wrappee_box);

    updateVertexArray();

    // m_close_btn.onResize(thickness, thickness);
    // m_close_btn.m_transf.m_offset = {m_size.x - thickness, 0};
}

void Frame::updateVertexArray()
{
    Vec2d size = getLayoutBox().getSize();

    m_vertex_array[0].position = {0,      0};
    m_vertex_array[1].position = {size.x, 0};
    m_vertex_array[2].position = {size.x, size.y};
    m_vertex_array[3].position = {0,      size.y};
}

void Frame::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    sf::VertexArray buf_vertex_array(m_vertex_array);
    for (int32_t i = 0; i < buf_vertex_array.getVertexCount(); ++i)
    {
        Vector2f pos = static_cast<Vector2f>(top_transf.apply(static_cast<Vec2d>(m_vertex_array[i].position)));
        buf_vertex_array[i].position = pos;
    }

    target.draw(buf_vertex_array);
    m_wrappee->draw(target, transf_list);

    // if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
    //     m_close_btn.draw(target, transf_list);

    transf_list.PopBack();
}

bool Frame::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    bool res = false;

    // if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
    // {
    //     res = res || m_close_btn.onMousePressed(key, x, y, transf_list);
    //     if (res)
    //     {
    //         transf_list.PopBack();
    //         return true;
    //     }
    // }

    Vec2d pos = top_transf.restore(Vec2d(x, y));
    // cringe for compatibility only
    Vec2d m_size = getLayoutBox().getSize();

    if (EPS < pos.x && pos.x < m_size.x    - EPS &&
        EPS < pos.y && pos.y < m_thickness - EPS)
    {
        m_status = status_t::HOLD;
        m_hold_pos = pos;

        res = true;
    }

    if (EPS + m_wrappee->getLayoutBox().getSize().x + m_thickness < pos.x && pos.x < m_size.x - EPS &&
        EPS + m_thickness < pos.y && pos.y < m_size.y - EPS)
    {
        m_status = (status_t) ((uint8_t) m_status | (uint8_t) status_t::HOLD_HOR);
        m_hold_pos = pos;

        res = true;
    }

    if (EPS + m_thickness < pos.x && pos.x < m_size.x - EPS &&
        EPS + m_thickness + m_wrappee->getLayoutBox().getSize().y  < pos.y && pos.y < m_size.y)
    {
        m_status = (status_t) ((uint8_t) m_status | (uint8_t) status_t::HOLD_VER);
        m_hold_pos = pos;

        res = true;
    }

    res = res || m_wrappee->onMousePressed(key, x, y, transf_list);

    transf_list.PopBack();

    return res;
}

bool Frame::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    bool res = false;

    // if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
    // {
    //     res = res || m_close_btn.onMouseReleased(key, x, y, transf_list);
    //     if (res)
    //     {
    //         transf_list.PopBack();
    //         return true;
    //     }
    // }

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (m_status != status_t::DEFAULT)
    {
        m_status = status_t::DEFAULT;
        res = true;
    }

    res = res || m_wrappee->onMouseReleased(key, x, y, transf_list);

    transf_list.PopBack();

    return res;
}

bool Frame::onResize(float width, float height)
{
    bool res = m_wrappee->onResize(width - 2 * m_thickness, height - 2 * m_thickness);
    if (!res)
        return false;

    // m_size = Vec2d(width, height);
    getLayoutBox().setSize(Vec2d(width, height));
    m_wrappee->getLayoutBox().onParentUpdate(getLayoutBox());
    // printf("frame size: %f %f\n", width, height);
    // m_close_btn.m_transf.m_offset = {width - m_thickness, 0};
    updateVertexArray();
    return true;
}

bool Frame::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // cringe for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
    
    bool res = false;

    // if ((uint8_t) m_interactive & (uint8_t) interactive_t::CLOSABLE)
    // {
    //     res = res || m_close_btn.onMouseMoved(x, y, transf_list);
    //     if (res)
    //     {
    //         transf_list.PopBack();
    //         return true;
    //     }
    // }

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (m_status == status_t::HOLD)
    {
        Vec2d delta_hold_pos = pos - m_hold_pos;
        Vec2d new_pos = getLayoutBox().getPosition() + delta_hold_pos * top_transf.getScale();
        getLayoutBox().setPosition(new_pos);
        res = true;
    }

    if ((uint8_t) m_status & (uint8_t) status_t::HOLD_HOR)
    {
        Vec2d delta_hold_pos = pos - m_hold_pos;
        onResize(getLayoutBox().getSize().x + delta_hold_pos.x * top_transf.getScale().x, getLayoutBox().getSize().y);
        m_hold_pos.x = getLayoutBox().getSize().x;
        res = true;
    }

    if ((uint8_t) m_status & (uint8_t) status_t::HOLD_VER)
    {
        Vec2d delta_hold_pos = pos - m_hold_pos;
        onResize(getLayoutBox().getSize().x, getLayoutBox().getSize().y + delta_hold_pos.y * top_transf.getScale().y);
        m_hold_pos.y = getLayoutBox().getSize().y;
        res = true;
    }

    res = res || m_wrappee->onMouseMoved(x, y, transf_list);

    transf_list.PopBack();
    return res;
}

bool Frame::onKeyboardPressed(KeyboardKey key)
{
    m_wrappee->onKeyboardPressed(key);
}

bool Frame::onKeyboardReleased(KeyboardKey key)
{
    m_wrappee->onKeyboardReleased(key);
}

bool Frame::onTime(float d_seconds)
{
    m_wrappee->onTime(d_seconds);
}

// void Frame::setClosable(bool flag)
// {
//     if (flag)
//         m_interactive = (interactive_t) ((uint8_t) m_interactive | (uint8_t) interactive_t::CLOSABLE);
//     else
//         m_interactive = (interactive_t) ((uint8_t) m_interactive & ~((uint8_t) interactive_t::CLOSABLE));
// }
// 
// void Frame::CloseButton::setContainer(Container &container)
// {
//     m_container = &container;
// }
// 
// void Frame::CloseButton::setCloseId(int32_t id)
// {
//     m_close_id = id;
// }
// 
// void Frame::setContainer(Container &container)
// {
//     m_close_btn.setContainer(container);
// }
// 
// void Frame::setCloseId(int32_t id)
// {
//     m_close_btn.setCloseId(id);
// }
// 
// bool Frame::CloseButton::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
// {
//     bool flag = Button::onMousePressed(key, x, y, transf_list);
//     if (flag)
//         m_container->close(m_close_id);
// 
//     return flag;
// }

