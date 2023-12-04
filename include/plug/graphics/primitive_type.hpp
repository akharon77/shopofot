#ifndef PLUG_GRAPHICS_PRIMITIVE_TYPE_HPP
#define PLUG_GRAPHICS_PRIMITIVE_TYPE_HPP

namespace plug
{
    enum PrimitiveType
    {
        Points,
        Lines,
        LineStrip,
        Triangles,
        TriangleStrip,
        TriangleFan,
        Quads,
        LinesStrip = LineStrip,
        TrianglesStrip = TriangleStrip,
        TrianglesFan = TriangleFan,
    };

} // namespace plug

#endif  // PLUG_GRAPHICS_PRIMITIVE_TYPE_HPP

