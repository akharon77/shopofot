#ifndef UI_BUTTON_TOGGLE_BUTTON_HPP
#define UI_BUTTON_TOGGLE_BUTTON_HPP

#include "ui/button/button.hpp"

class ToggleButton : public Button
{
    bool m_is_toggled;

public:
    ~ToggleButton() = default;
    ToggleButton& operator = (const ToggleButton &rhs) = default;
    ToggleButton(const ToggleButton &rhs) = default;

    ToggleButton(const plug::LayoutBox &box, ButtonTexture &btn_texture);

    void setToggle(bool flag) { m_is_toggled = flag; if (!flag) setRect(m_btn_texture.m_default_rect);}

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
};

#endif  // UI_BUTTON_TOGGLE_BUTTON_HPP

