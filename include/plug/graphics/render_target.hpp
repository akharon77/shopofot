#ifndef PLUG_GRAPHICS_RENDER_TARGET_HPP
#define PLUG_GRAPHICS_RENDER_TARGET_HPP

#include "plug/graphics/texture.hpp"
#include "plug/graphics/vertex_array.hpp"

#include <SFML/Graphics.hpp>

namespace plug
{
    class RenderTarget
    {
    public:
        virtual ~RenderTarget(void) = default;

        virtual void draw  (const VertexArray &array)                         = 0;
        virtual void draw  (const VertexArray &array, const Texture &texture) = 0;

        virtual void clear(Color color) = 0;

        virtual void setActive(bool active) = 0;

        virtual sf::RenderTarget &getSFMLRenderTarget() = 0;
    };

} // namespace plug

#endif  // PLUG_GRAPHICS_RENDER_TARGET_HPP

