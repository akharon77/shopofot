#include "ui/button/toggle_button.hpp"

ToggleButton::ToggleButton(const plug::LayoutBox &box, ButtonTexture &btn_texture) :
    Button(box, btn_texture),
    m_is_toggled(false)
{}

void ToggleButton::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    if (m_is_toggled)
        setRect(m_btn_texture.m_pressed_rect);

    Button::draw(stack, target);
}

void ToggleButton::onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context)
{
    Button::onMousePressed(key, x, y, context);
    if (context.stopped)
        m_is_toggled = true;
}

