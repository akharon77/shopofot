#ifndef UI_BUTTON_TEXT_BUTTON_HPP
#define UI_BUTTON_TEXT_BUTTON_HPP

#include "ui/button/button.hpp"

struct TextButtonTexture
{
    // double      thickness;
    plug::Color    color;
    ButtonTexture *btn_texture;
};

class TextButton : public Button
{
    double      m_thickness;
    plug::Color m_color;
    const char *m_str;

public:
    TextButton(const plug::LayoutBox &box, const char *str, TextButtonTexture &btn_texture);

    ~TextButton() = default;
    TextButton& operator = (const TextButton &rhs) = default;
    TextButton(const TextButton &rhs) = default;

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;
};

#endif // UI_BUTTON_TEXT_BUTTON_HPP

