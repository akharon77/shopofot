#ifndef FRAME_HPP
#define FRAME_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "button.hpp"

class Frame : public Widget
{
    friend class CloseButton;

    class CloseButton : public Button
    {
        Frame *m_frame;

    public:
        CloseButton(Frame &frame, const ButtonTexture &btn_texture) :
            Button({0, 0}, 0, 0, btn_texture)
        {};

        ~CloseButton() = default;

        CloseButton(const CloseButton &rhs) = delete;
        CloseButton& operator = (const CloseButton& rhs) = delete;

        virtual void onClick() {};
    };

    enum status_t
    {
        DEFAULT  = 0,
        HOLD     = 1,
        HOLD_VER = 1 << 1,
        HOLD_HOR = 1 << 2
    };

    Widget *m_wrappee;

    const char *m_title;

    float m_thickness;

    float m_width;
    float m_height;

    sf::VertexArray m_vertex_array;

    status_t m_status;
    Vector2f m_hold_pos;

    sf::Texture *m_texture;
    sf::IntRect  m_rect;

    CloseButton m_close_btn;

    void updateVertexArray();

public:
    Frame(Widget &wrappee, const char *title, float thickness, const ButtonTexture &close_btn_texture);

    ~Frame() = default;
    Frame& operator = (const Frame &rhs) = delete;
    Frame(const Frame &rhs) = delete;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onResize(float width, float height) override;

    virtual bool onTime (float d_seconds) override;
};

#endif  // FRAME_HPP

