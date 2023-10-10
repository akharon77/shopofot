#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "widget.hpp"

const uint32_t SCREEN_WIDTH  = 1024; 
const uint32_t SCREEN_HEIGHT = 720;

struct WindowTexture
{
    sf::Texture *m_texture;
    sf::IntRect  m_rect;
};

class Window : public Widget
{
    float m_width;
    float m_height;

    WindowTexture   *m_texture;
    sf::VertexArray  m_vertex_arr;

    // sf::Sprite   m_sprite;

public:
    Window(Vector2f pos, float width, float height, WindowTexture &texture);  // sf::Texture &texture, const sf::IntRect &rect);

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

// class WindowDecorator : public Widget
// {
//     Widget *m_wrappee;
// 
// public:
//     WindowDecorator(Widget *wrappee);
// 
//     ~WindowDecorator() = default;
//     WindowDecorator& operator = (const WindowDecorator &rhs) = delete;
//     WindowDecorator(const WindowDecorator &rhs) = delete;
// 
//     virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;
// 
//     virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
//     virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
// 
//     virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;
// 
//     virtual bool onKeyboardPressed  (KeyboardKey key) override;
//     virtual bool onKeyboardReleased (KeyboardKey key) override;
// 
//     virtual bool onTime (float d_seconds) override;
// };

#endif  // WINDOW_HPP

