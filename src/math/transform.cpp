#include "math/transform.hpp"

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

