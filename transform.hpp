#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "vector2.hpp"

class Transform
{
public:
    Vector2f m_offset;
    Vector2f m_scale;

    Transform(const Vector2f &offset = {0, 0}, const Vector2f &scale = {1, 1});

    ~Transform()                                 = default;
    Transform(const Transform &rhs)              = default;
    Transform& operator = (const Transform &rhs) = default;

    Transform applyParent    (const Transform &par) const;

    Vector2f    applyTransform (const Vector2f &vec) const;  // from global to local
    Vector2f rollbackTransform (const Vector2f &vec) const;  // from local to global
};

#endif  // TRANSFORM_HPP

