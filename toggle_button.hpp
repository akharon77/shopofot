#ifndef TOGGLE_BUTTON_HPP
#define TOGGLE_BUTTON_HPP

#include "button.hpp"

class ToggleButton : public Button
{
    bool m_is_toggled;

public:
    ~ToggleButton() = default;
    ToggleButton& operator = (const ToggleButton &rhs) = default;
    ToggleButton(const ToggleButton &rhs) = default;

    ToggleButton(Vector2f pos, float width, float height, ButtonTexture &btn_texture);

    void setToggle(bool flag) { m_is_toggled = flag; if (!flag) setRect(m_btn_texture.m_default_rect);}

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;
};

#endif  // TOGGLE_BUTTON_HPP

