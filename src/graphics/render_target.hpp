#ifndef GRAPHICS_RENDER_TARGET_HPP
#define GRAPHICS_RENDER_TARGET_HPP

#include <SFML/Graphics/RenderTarget.hpp>

class RenderTarget : public plug::RenderTarget
{
    sf::RenderTarget &m_target;

public:
    RenderTarget(sf::RenderTarget &target) : m_target(target) {}
    ~RenderTarget(void) = default;

    virtual void draw  (const VertexArray &array)                         override;
    virtual void draw  (const VertexArray &array, const Texture &texture) override;

    virtual void clear(Color color) override;

    virtual void setActive(bool active) override;
};

#endif  // GRAPHICS_RENDER_TARGET_HPP

