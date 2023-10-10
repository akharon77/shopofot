#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "button.hpp"

struct ScrollBarTexture
{
    sf::Texture   *m_background;

    ButtonTexture *m_btn_up;
    ButtonTexture *m_btn_down;
    ButtonTexture *m_btn_left;
    ButtonTexture *m_btn_right;

    ButtonTexture *m_btn_scroll;
};

class ScrollBar : public Widget
{
protected:
    enum scroll_button_t
    {
        VER,
        HOR
    };

    friend class ScrollButton;
    friend class ScrollDeltaButton;

    class ScrollButton : public Button
    {
        enum status_t
        {
            DEFAULT,
            HOLD
        };

        scroll_button_t m_type;
        status_t m_status;
        Vector2f m_hold_pos;
        ScrollBar *m_scrollbar;

    public:
        ScrollButton(ScrollBar &scrollbar, scroll_button_t btn_type, ButtonTexture &btn_texture);

        ~ScrollButton() = default;

        ScrollButton(const ScrollButton &rhs) = delete;
        ScrollButton& operator = (const ScrollButton& rhs) = delete;

        virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
        virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

        virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;
    };

    Widget *m_wrappee;

    float m_thickness;

    float m_width;
    float m_height;

    bool m_is_ver;
    bool m_is_hor;

    ScrollBarTexture *m_texture;

    ScrollButton m_btn_ver;
    // ScrollDeltaButton m_btn_up;
    // ScrollDeltaButton m_btn_down;

    ScrollButton m_btn_hor;
    // ScrollDeltaButton m_btn_left;
    // ScrollDeltaButton m_btn_right;

public:
    ScrollBar(Widget &wrappee, float thickness, float width, bool is_hor, float height, bool is_ver, ScrollBarTexture &texture);

    ~ScrollBar() = default;
    ScrollBar& operator = (const ScrollBar &rhs) = delete;
    ScrollBar(const ScrollBar &rhs) = delete;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onResize(float width, float height) override;

    virtual bool onTime (float d_seconds) override;
};

#endif  // SCROLLBAR_HPP 

