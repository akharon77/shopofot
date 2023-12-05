#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

#include "graphics/render_texture.hpp"
#include "util/sfml.hpp"

RenderTexture::RenderTexture(sf::RenderTexture &sf_texture, size_t width, size_t height) :
    m_sf_texture(sf_texture),
    m_plug_texture(new plug::Texture(width, height)),
    m_flag_upd(true),
    m_width(width),
    m_height(height)
{
    m_sf_texture.create(width, height);
    m_sf_texture.clear(sf::Color::Transparent);
    m_sf_texture.display();
}

void RenderTexture::create(size_t width, size_t height)
{
    m_sf_texture.create(width, height);
    m_sf_texture.clear(sf::Color::Transparent);
    m_sf_texture.display();
    m_width = width;
    m_height = height;
    m_flag_upd = true;

    delete m_plug_texture;
    m_plug_texture = new plug::Texture(width, height);
}

const sf::RenderTexture& RenderTexture::getSfTexture()
{
    return m_sf_texture;
}

const plug::Texture& RenderTexture::getPlugTexture()
{
    if (m_flag_upd)
    {
        m_flag_upd = false;
        sf::Image image = m_sf_texture.getTexture().copyToImage();

        for (size_t y = 0; y < m_height; ++y)
        {
            for (size_t x = 0; x < m_width; ++x)
            {
                sf::Color color = image.getPixel(x, y);
                m_plug_texture->setPixel(x, y, getPlugColor(color));
            }
        }
    }

    return *m_plug_texture;
}

void RenderTexture::draw(const plug::VertexArray &array)
{
    sf::VertexArray sf_array;
    copyToSFMLVertexArray(sf_array, array);

    m_sf_texture.draw(sf_array);
    m_sf_texture.display();
    m_flag_upd = true;
}

void RenderTexture::draw(const plug::VertexArray &array, const plug::Texture &texture)
{
    sf::VertexArray sf_array;
    copyToSFMLVertexArray(sf_array, array);

    sf::Texture sf_texture;
    copyToSFMLTexture(sf_texture, texture);

    m_sf_texture.draw(sf_array, &sf_texture);
    m_sf_texture.display();
    m_flag_upd = true;
}

void RenderTexture::clear(plug::Color color)
{
    m_sf_texture.clear(getSFMLColor(color));
    m_sf_texture.display();
    m_flag_upd = true;
}

void RenderTexture::setActive(bool active)
{
    m_sf_texture.setActive(active);
}

