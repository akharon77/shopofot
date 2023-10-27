#include "text_btn.hpp"

TextButton::TextButton(const Vector2f &pos, float width, float height, const char *str, sf::Font &font, int32_t char_size, const ButtonTexture &btn_texture) : 
    Button(pos, width, height, btn_texture)
{
    m_text.setFont(font);
    m_text.setString(str);
    m_text.setCharacterSize(char_size);
}

void TextButton::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    Button::draw(target, transf_list);

    transf_list.PushBack(m_transf.applyParent(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vector2f pos = top_transf.rollbackTransform({0, 0});
    
    m_text.setPosition(pos);
    target.draw(m_text);

    transf_list.PopBack();
}
