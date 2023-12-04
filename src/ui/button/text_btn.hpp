#ifndef TEXT_BTN_HPP
#define TEXT_BTN_HPP

#include <SFML/Graphics/Text.hpp>

#include "button.hpp"

struct TextButtonTexture
{
    sf::Font *m_font;
    int32_t m_char_size;
    ButtonTexture *m_btn_texture;
};

class TextButton : public Button
{
    sf::Text m_text;

public:
    TextButton(const LayoutBox &box, const char *str, TextButtonTexture &btn_texture);

    ~TextButton() = default;
    TextButton& operator = (const TextButton &rhs) = default;
    TextButton(const TextButton &rhs) = default;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;
};

#endif // TEXT_BTN_HPP

