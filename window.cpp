#include "window.hpp"

Window::Window(Vector2f pos, float width, float height, sf::Texture &texture, const sf::IntRect &rect) :
    m_width  (width),
    m_height (height),
    m_transf (pos, Vector2f{width / rect.width, height / rect.height}),
    m_sprite (texture, rect)
{}

void Window::draw(sf::RenderWindow &target, List<Transform> &transf_list)
{
    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    m_sprite.setPosition(top_transf.m_offset);
    printf("%f %f\n", m_sprite.getPosition().x, m_sprite.getPosition().y);
    m_sprite.setScale(top_transf.m_scale);
    target.draw(m_sprite);

    transf_list.PopBack();
}

bool Window::onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}
bool Window::onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}

bool Window::onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) {}

bool Window::onKeyboardPressed  (KeyboardKey key) {}
bool Window::onKeyboardReleased (KeyboardKey key) {}

bool Window::onTime (float d_seconds) {}

