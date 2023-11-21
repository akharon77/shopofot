#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "vector2d.hpp"

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

// class Transform
// {
// public:
//     Vector2f m_offset;
//     Vector2f m_scale;
// 
//     Transform(const Vector2f &offset = {0, 0}, const Vector2f &scale = {1, 1});
// 
//     ~Transform()                                 = default;
//     Transform(const Transform &rhs)              = default;
//     Transform& operator = (const Transform &rhs) = default;
// 
//     Transform applyParent    (const Transform &par) const;
// 
//     Vector2f    applyTransform (const Vector2f &vec) const;  // from global to local
//     Vector2f rollbackTransform (const Vector2f &vec) const;  // from local to global
// };

#endif  // TRANSFORM_HPP

