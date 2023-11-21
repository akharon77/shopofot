#include "transform.hpp"

Transform::Transform(const Vec2d &offset, const Vec2d &scale) :
    m_offset(offset), m_scale(scale)
{}

Vec2d Transform::getOffset() const
{
    return m_offset;
}

void Transform::setOffset(const Vec2d &offset)
{
    m_offset = offset;
}

Vec2d Transform::getScale() const
{
    return m_scale;
}

void Transform::setScale(const Vec2d &scale)
{
    m_scale = scale;
}

// from local to global
Vec2d Transform::apply(const Vec2d &vec) const
{
    return m_offset + vec * m_scale;
}

// from global to local
Vec2d Transform::restore(const Vec2d &vec) const
{
    return (vec - m_offset) / m_scale;
}

Transform Transform::combine(const Transform &parent_transform) const
{
    return Transform
           {
               parent_transform.getOffset() + m_offset * parent_transform.getScale(),
               m_scale * parent_transform.getScale()
           };
}

// Transform::Transform(const Vector2f &offset, const Vector2f &scale) :
//     m_offset (offset),
//     m_scale  (scale)
// {}
// 
// Transform Transform::applyParent(const Transform &par) const
// {
//     return Transform
//     {
//         par.m_offset + Vector2f{par.m_scale.x * m_offset.x, par.m_scale.y * m_offset.y},
//         {
//             m_scale.x * par.m_scale.x,
//             m_scale.y * par.m_scale.y
//         }
//     };
// }
// 
// Vector2f Transform::applyTransform(const Vector2f &vec) const
// {
//     Vector2f res = vec - m_offset;
//     res.x /= m_scale.x;
//     res.y /= m_scale.y;
// 
//     return res;
// }
// 
// Vector2f Transform::rollbackTransform (const Vector2f &vec) const
// {
//     return m_offset + Vector2f{vec.x * m_scale.x, vec.y * m_scale.y};
// }

