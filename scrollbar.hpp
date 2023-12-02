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
        Vec2d m_hold_pos;
        ScrollBar *m_scrollbar;

    public:
        ScrollButton(ScrollBar &scrollbar, scroll_button_t btn_type, ButtonTexture &btn_texture);

        ~ScrollButton() = default;

        ScrollButton(const ScrollButton &rhs) = default;
        ScrollButton& operator = (const ScrollButton& rhs) = default;

        virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
        virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

        virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;
    };

    class ScrollDeltaButton : public Button
    {
        Vec2d m_delta;
        ScrollBar &m_scrollbar;

    public:
        ScrollDeltaButton(ScrollBar &scrollbar, const Vec2d &delta, ButtonTexture &btn_texture);

        ~ScrollDeltaButton() = default;

        ScrollDeltaButton(const ScrollDeltaButton &rhs) = default;
        ScrollDeltaButton& operator = (const ScrollDeltaButton& rhs) = default;

        virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    };

    Widget *m_wrappee;

    double m_thickness;

    LayoutBox *m_wrappee_stolen_layout_box;

    // visible area params
    double m_width;
    double m_height;

    bool m_is_ver;
    bool m_is_hor;

    ScrollBarTexture *m_texture;

    ScrollButton m_btn_ver;
    ScrollButton m_btn_hor;

    ScrollDeltaButton m_btn_up;
    ScrollDeltaButton m_btn_down;

    ScrollDeltaButton m_btn_left;
    ScrollDeltaButton m_btn_right;

    double m_hor_per;
    double m_ver_per;

    static double clip(double perc);

    void updateButtonsSizes();
    void updateComponentsPositionsByPercents();

public:
    enum scrollable_t : uint16_t
    {
        SCROLLABLE_NONE       = 0x00,
        SCROLLABLE_VERTICAL   = 0x01,
        SCROLLABLE_HORIZONTAL = 0x02
    };

    ScrollBar(Widget &wrappee, const Length &thickness, const Length &width, const Length &height, scrollable_t type, ScrollBarTexture &texture);

    ~ScrollBar() = default;
    ScrollBar& operator = (const ScrollBar &rhs) = default;
    ScrollBar(const ScrollBar &rhs) = default;

    Vec2d getPrefferedButtonsSizes() const;

    Vec2d getPercentageCovering() const;
    Vec2d getPercentageOffset  () const;

    void setPercentageOffset   (const Vec2d &perc);
    void deltaPercentageOffset (const Vec2d &delta);

    double getThickness() const;

    Vec2d getVisibleAreaSize() const;
    Vec2d getWrappeeSize() const;

    // const LayoutBox& getWrappeeBox() const;

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

