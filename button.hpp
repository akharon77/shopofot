#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "widget.hpp"
#include "vector2.hpp"

struct ButtonTexture
{
    const sf::Texture *m_texture;

    sf::IntRect  m_default_rect;
    sf::IntRect  m_pressed_rect;
    sf::IntRect  m_focused_rect;

    ButtonTexture(const sf::Texture &texture, const sf::IntRect &default_rect, const sf::IntRect &pressed_rect, const sf::IntRect &focused_rect);

    ~ButtonTexture() = default;
    ButtonTexture(const ButtonTexture &rhs) = default;
    ButtonTexture& operator = (const ButtonTexture &rhs) = default;
};

class Button : public Widget
{
    enum Status
    {
        DEFAULT,
        PRESSED,
        FOCUSED
    };

    Status m_status;

    float m_width;
    float m_height;

    Transform m_transf;

    ButtonTexture m_btn_texture;

    sf::VertexArray m_vertex_array;

    void setRect(const sf::IntRect &rect);

public:
    Button(const Vector2f &pos, float width, float height, const ButtonTexture &btn_texture);

    ~Button() = default;
    Button& operator = (const Button &rhs) = delete;
    Button(const Button &rhs) = delete;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) {};
    virtual bool onKeyboardReleased (KeyboardKey key) {};

    virtual bool onTime (float d_seconds) {};

    virtual void onClick()    = 0;
    // virtual void onReleased() = 0;
};

#endif  // BUTTON_HPP

