#ifndef UTIL_SFML_HPP
#define UTIL_SFML_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "graphics.hpp"

sf::Color    getSFMLColor    (const plug::Color &plug_color);
sf::Vector2f getSFMLVector2f (const plug::Vec2d &plug_vector);

plug::Color getPlugColor  (const sf::Color    &sf_color);
plug::Vec2d getPlugVector (const sf::Vector2f &sf_vector);
plug::Vec2d getPlugVector (const sf::Vector2u &sf_vector);
plug::Vec2d getPlugVector (const sf::Vector2i &sf_vector);

void copyToSFMLVertex      (sf::Vertex      &sf_vertex,  const plug::Vertex      &plug_vertex);
void copyToSFMLVertexArray (sf::VertexArray &sf_array,   const plug::VertexArray &plug_array);
void copyToSFMLTexture     (sf::Texture     &sf_texture, const plug::Texture     &plug_texture);

#endif  // UTIL_SFML_HPP

