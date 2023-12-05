#include "graphics/render_window.hpp"
#include "util/sfml.hpp"

void RenderWindow::draw(const plug::VertexArray &array)
{
    sf::VertexArray sf_array;
    copyToSFMLVertexArray(sf_array, array);

    m_window.draw(sf_array);
}

void RenderWindow::draw(const plug::VertexArray &array, const plug::Texture &texture)
{
    sf::VertexArray sf_array;
    copyToSFMLVertexArray(sf_array, array);

    sf::Texture sf_texture;
    copyToSFMLTexture(sf_texture, texture);

    m_window.draw(sf_array, &sf_texture);
}

void RenderWindow::clear(plug::Color color)
{
    m_window.clear(getSFMLColor(color));
}

void RenderWindow::setActive(bool active)
{
    m_window.setActive(active);
}

