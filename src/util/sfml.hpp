#ifndef UTIL_SFML_HPP
#define UTIL_SFML_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "graphics.hpp"

sf::Color    getSFMLColor    (const Color &plug_color);
sf::Vector2f getSFMLVector2f (const Vec2d &plug_vector);

Color getPlugColor  (const sf::Color    &sf_color);
Vec2d getPlugVector (const sf::Vector2f &sf_vector);
Vec2d getPlugVector (const sf::Vector2u &sf_vector);
Vec2d getPlugVector (const sf::Vector2i &sf_vector);

void copyToSFMLVertex      (sf::Vertex      &sf_vertex,  const Vertex      &plug_vertex);
void copyToSFMLVertexArray (sf::VertexArray &sf_array,   const VertexArray &plug_array);
void copyToSFMLTexture     (sf::Texture     &sf_texture, const Texture     &plug_texture);

#endif  // UTIL_SFML_HPP

