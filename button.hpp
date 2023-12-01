#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "widget.hpp"
#include "vector2d.hpp"

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

    // float m_width;
    // float m_height;

public:
    Button(const LayoutBox &box, const ButtonTexture &btn_texture);

    ~Button() = default;
    Button& operator = (const Button &rhs) = default;
    Button(const Button &rhs) = default;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) {};
    virtual bool onKeyboardReleased (KeyboardKey key) {};

    virtual bool onResize(float width, float height);

    virtual bool onTime (float d_seconds) {};
};

#endif  // BUTTON_HPP

