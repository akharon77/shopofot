#include "ui/button/text_button.hpp"
#include "graphics/shapes.hpp"

#include <cstring>
#include <algorithm>

#include <SFML/Graphics/Text.hpp>

TextButton::TextButton(const plug::LayoutBox &box, const char *str, int32_t thickness, TextButtonTexture &btn_texture) :
    Button(box, *btn_texture.btn_texture),
    m_thickness(thickness),
    m_color(btn_texture.color),
    m_str(str),
    m_font(btn_texture.font)
{
    int32_t len = strlen(str);
    // m_thickness = 20;
}

void TextButton::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Button::draw(stack, target);

    Transform own_transf(getLayoutBox().getPosition(), Vec2d(1, 1));
    stack.enter(own_transf);

    Vec2d pos = stack.apply(Vec2d(0, 0.5 * (getLayoutBox().getSize().y - m_thickness)));
    
    // drawText(target, pos, m_str, m_thickness, m_color);

    pos += Vec2d(m_thickness * 0.05, m_thickness * 0.05);

    sf::Text text;
    text.setFont(m_font);
    text.setString(m_str);
    text.setCharacterSize(m_thickness);
    text.setPosition(pos.x, pos.y);
    target.getSFMLRenderTarget().draw(text);

    stack.leave();
}

