#ifndef GRAPHICS_RENDER_TARGET_HPP
#define GRAPHICS_RENDER_TARGET_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include "plug/graphics/render_target.hpp"

class RenderTarget : public plug::RenderTarget
{
    sf::RenderTarget &m_target;

public:
    RenderTarget(sf::RenderTarget &target) : m_target(target) {}
    ~RenderTarget(void) = default;

    virtual void draw (const plug::VertexArray &array) override;
    virtual void draw (const plug::VertexArray &array, const plug::Texture &texture) override;

    virtual void clear(plug::Color color) override;

    virtual void setActive(bool active) override;
};

#endif  // GRAPHICS_RENDER_TARGET_HPP

