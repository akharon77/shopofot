#include "toggle_button.hpp"

ToggleButton::ToggleButton(Vector2f pos, float width, float height, ButtonTexture &btn_texture) :
    Button(pos, width, height, btn_texture),
    m_is_toggled(false)
{}

void ToggleButton::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    if (m_is_toggled)
        setRect(m_btn_texture.m_pressed_rect);

    Button::draw(target, transf_list);
}

bool ToggleButton::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = Button::onMousePressed(key, x, y, transf_list);
    if (res)
        m_is_toggled = true;

    return res;
}

bool ToggleButton::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = Button::onMouseReleased(key, x, y, transf_list);
    return res;
}

bool ToggleButton::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    bool res = Button::onMouseMoved(x, y, transf_list);
    return res;
}

