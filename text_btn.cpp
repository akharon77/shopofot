#include "text_btn.hpp"

TextButton::TextButton(const LayoutBox &box, const char *str, TextButtonTexture &btn_texture) :
    Button(box, *btn_texture.m_btn_texture)
{
    m_text.setFont(*btn_texture.m_font);
    m_text.setString(str);
    m_text.setCharacterSize(btn_texture.m_char_size);
}

void TextButton::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    Button::draw(target, transf_list);

    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vec2d pos = top_transf.apply(Vec2d(0, 0));
    
    m_text.setPosition(static_cast<Vector2f>(pos));
    target.draw(m_text);

    transf_list.PopBack();
}

