#ifndef PLUG_MATH_TRANSFORM_HPP
#define PLUG_MATH_TRANSFORM_HPP

#include "plug/math/vec2d.hpp"

class Transform
{
    Vec2d m_offset;
    Vec2d m_scale;

public:
    explicit Transform(const Vec2d &offset = Vec2d(),
                       const Vec2d &scale  = Vec2d(1, 1));

    Vec2d getOffset (void) const;
    Vec2d getScale  (void) const;

    void setOffset (const Vec2d &offset);
    void setScale  (const Vec2d &scale);

    // from local to global
    Vec2d apply(const Vec2d &vec) const;

    // from global to local
    Vec2d restore(const Vec2d &vec) const;

    Transform combine(const Transform &parent_transform) const;
};

#endif  // PLUG_MATH_TRANSFORM_HPP

