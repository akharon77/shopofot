#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "window.hpp"

class Canvas : public Window 
{
    float m_width;
    float m_height;

    sf::Sprite   m_sprite;

public:
    Window(Vector2f pos, float width, float height, sf::Texture &texture, const sf::IntRect &rect);

    ~Window() = default;
    Window& operator = (const Window &rhs) = delete;
    Window(const Window &rhs) = delete;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onResize(float width, float height) override;

    virtual bool onTime (float d_seconds) override;
};

#endif  // CANVAS_HPP

