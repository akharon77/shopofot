#ifndef PLUG_GRAPHICS_RENDER_TARGET_HPP
#define PLUG_GRAPHICS_RENDER_TARGET_HPP

#include "Plug/Graphics/Texture.h"
#include "Plug/Graphics/VertexArray.h"

namespace plug
{
    class RenderTarget
    {
    public:
        virtual ~RenderTarget(void) = default;

        virtual void draw  (const VertexArray &array) = 0;
        virtual void draw  (const VertexArray &array, const Texture &texture) = 0;

        virtual void clear(Color color) = 0;

        virtual void setActive(bool active) = 0;
    };

} // namespace plug

#endif  // PLUG_GRAPHICS_RENDER_TARGET_HPP

