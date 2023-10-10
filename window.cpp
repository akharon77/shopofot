#include "window.hpp"

Window::Window(Vector2f pos, float width, float height, sf::Texture &texture, const sf::IntRect &rect) :
    Widget({pos, Vector2f{width / rect.width, height / rect.height}}, {width, height}),
    m_width  (width),
    m_height (height),
    m_sprite (texture, rect)
{}

void Window::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    m_sprite.setPosition(top_transf.m_offset);
    m_sprite.setScale(top_transf.m_scale);

    target.draw(m_sprite);

    transf_list.PopBack();
}

bool Window::onResize(float width, float height)
{
    m_transf.m_scale = Vector2f{m_transf.m_scale.x / m_width * width, m_transf.m_scale.y / m_height * height};
    m_size = {width, height};
    m_width = width;
    m_height = height;

    return true;
}

bool Window::onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}
bool Window::onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}

bool Window::onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) {}

bool Window::onKeyboardPressed  (KeyboardKey key) {}
bool Window::onKeyboardReleased (KeyboardKey key) {}

bool Window::onTime (float d_seconds) {}

// WindowDecorator::WindowDecorator(Widget *wrappee) :
//     m_wrappee(wrappee)
// {}
// 
// void WindowDecorator::draw(sf::RenderTarget &target, List<Transform> &transf_list)
// {
//     m_wrappee->draw(target, transf_list);
// }
// 
// bool WindowDecorator::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
// {
//     m_wrappee->onMousePressed(key, x, y, transf_list);
// }
// 
// bool WindowDecorator::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
// {
//     m_wrappee->onMouseReleased(key, x, y, transf_list);
// }
// 
// bool WindowDecorator::onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list)
// {
//     m_wrappee->onMouseMoved(x, y, transf_list);
// }
// 
// bool WindowDecorator::onKeyboardPressed  (KeyboardKey key)
// {
//     m_wrappee->onKeyboardReleased(key);
// }
// 
// bool WindowDecorator::onKeyboardReleased (KeyboardKey key)
// {
//     m_wrappee->onKeyboardReleased(key);
// }
// 
// bool WindowDecorator::onTime (float d_seconds)
// {
//     m_wrappee->onTime(d_seconds);
// }

