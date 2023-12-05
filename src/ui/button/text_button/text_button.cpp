#include "ui/button/text_button.hpp"
#include "graphics/shapes.hpp"

#include <cstring>
#include <algorithm>

static const double CORRELATION_COEFF = 7.2;

TextButton::TextButton(const plug::LayoutBox &box, const char *str, TextButtonTexture &btn_texture) :
    Button(box, *btn_texture.btn_texture),
    m_thickness(-1),
    m_color(btn_texture.color),
    m_str(str)
{
    int32_t len = strlen(str);
    m_thickness = box.getSize().x / len / CORRELATION_COEFF;
}

void TextButton::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Button::draw(stack, target);

    Transform own_transf(getLayoutBox().getPosition(), Vec2d(1, 1));
    stack.enter(own_transf);

    Vec2d pos = stack.apply(Vec2d(0, 0.5 * (getLayoutBox().getSize().y - m_thickness)));
    
    drawText(target, pos, m_str, m_thickness, m_color);

    stack.leave();
}

