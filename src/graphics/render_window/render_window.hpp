#ifndef GRAPHICS_RENDER_WINDOW_HPP
#define GRAPHICS_RENDER_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "plug/graphics/render_target.hpp"

class RenderWindow : public plug::RenderTarget
{
    sf::RenderWindow &m_window;

public:
    RenderWindow(sf::RenderWindow &target) : m_window(window) {}
    ~RenderWindow(void) = default;

    virtual void draw (const plug::VertexArray &array) override;
    virtual void draw (const plug::VertexArray &array, const plug::Texture &texture) override;

    virtual void clear(plug::Color color) override;

    virtual void setActive(bool active) override;
};

#endif  // GRAPHICS_RENDER_WINDOW_HPP

