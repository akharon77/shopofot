#include "graphics/render_target.hpp"
#include "util/sfml.hpp"

void RenderTarget::draw(const plug::VertexArray &array)
{
    sf::VertexArray sf_array;
    copyToSFMLVertexArray(sf_array, array);

    m_target.draw(sf_array);
}

void RenderTarget::draw(const plug::VertexArray &array, const plug::Texture &texture)
{
    sf::VertexArray sf_array;
    copyToSFMLVertexArray(sf_array, array);

    sf::Texture sf_texture;
    copyToSFMLTexture(sf_texture, texture);

    m_target.draw(sf_array, &sf_texture);
}

void RenderTarget::clear(plug::Color color)
{
    m_target.clear(getSFMLColor(color));
}

void RenderTarget::setActive(bool active)
{
    m_target.setActive(active);
}
