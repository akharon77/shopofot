#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "graphics.hpp"
#include "math.hpp"

struct ButtonTexture
{
    const sf::Texture *m_texture;

    sf::IntRect  m_default_rect;
    sf::IntRect  m_pressed_rect;
    sf::IntRect  m_focused_rect;
};

class Button : public Widget
{
    sf::VertexArray m_vertex_array;

protected:
    enum Status
    {
        DEFAULT,
        PRESSED,
        FOCUSED
    };

    Status m_status;

    ButtonTexture m_btn_texture;

    void setRect(const sf::IntRect &rect);

public:
    Button(const LayoutBox &box, const ButtonTexture &btn_texture);

    ~Button() = default;
    Button& operator = (const Button &rhs) = default;
    Button(const Button &rhs) = default;

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual bool onTime(double d_seconds, plug::EHC &context) {}

    virtual bool onMouseMoved (double x, double y, plug::EHC &context) override;

    virtual bool onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
    virtual bool onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) override;

    virtual bool onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) {}
    virtual bool onKeyboardReleased (plug::KeyCode key, plug::EHC &context) {}

    virtual bool onResize(double width, double height, plug::EHC &context) override;
};

#endif  // BUTTON_HPP

