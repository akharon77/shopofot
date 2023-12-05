#include "ui/button/text_button.hpp"

TextButton::TextButton(const plug::LayoutBox &box, const char *str, TextButtonTexture &btn_texture) :
    Button(box, *btn_texture.m_btn_texture)
{
    m_text.setFont(*btn_texture.m_font);
    m_text.setString(str);
    m_text.setCharacterSize(btn_texture.m_char_size);
}

void TextButton::draw(plug::TransformStack &stack, plug::RenderTarget &target)
{
    Button::draw(stack, target);

    Transform own_transf(getLayoutBox().getPosition(), Vec2d(1, 1));
    stack.enter(own_transf);

    Vec2d pos = stack.apply(Vec2d(0, 0));
    
    m_text.setPosition(sf::Vector2f(pos.x, pos.y));
    target.draw(m_text);

    transf_list.PopBack();
}

