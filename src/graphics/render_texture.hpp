#ifndef GRAPHICS_RENDER_TEXTURE_HPP
#define GRAPHICS_RENDER_TEXTURE_HPP

#include <SFML/Graphics/RenderTexture.hpp>

#include "plug/graphics/render_target.hpp"
#include "plug/graphics/texture.hpp"

class RenderTexture : public plug::RenderTarget
{
    sf::RenderTexture &m_sf_texture;
    plug::Texture      m_plug_texture;

    bool   m_flag_upd;
    size_t m_width;
    size_t m_height;

public:
    RenderTexture(sf::RenderTexture &sf_texture, size_t width, size_t height);
    ~RenderTexture(void) = default;

    const     plug::Texture& getPlugTexture() const;
    const sf::RenderTexture& getSfTexture()   const;

    bool create(size_t width, size_t height);

    virtual void draw (const plug::VertexArray &array) override;
    virtual void draw (const plug::VertexArray &array, const plug::Texture &texture) override;

    virtual void clear(plug::Color color) override;

    virtual void setActive(bool active) override;
};

#endif  // GRAPHICS_RENDER_TEXTURE_HPP

