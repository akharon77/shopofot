#include "plug/math/transform.hpp"

plug::Transform::Transform(const plug::Vec2d &offset, const plug::Vec2d &scale) :
    m_offset(offset), m_scale(scale)
{}

plug::Vec2d plug::Transform::getOffset() const
{
    return m_offset;
}

void plug::Transform::setOffset(const plug::Vec2d &offset)
{
    m_offset = offset;
}

plug::Vec2d plug::Transform::getScale() const
{
    return m_scale;
}

void plug::Transform::setScale(const plug::Vec2d &scale)
{
    m_scale = scale;
}

// from local to global
plug::Vec2d plug::Transform::apply(const plug::Vec2d &vec) const
{
    return m_offset + vec * m_scale;
}

// from global to local
plug::Vec2d plug::Transform::restore(const plug::Vec2d &vec) const
{
    return (vec - m_offset) / m_scale;
}

plug::Transform plug::Transform::combine(const plug::Transform &parent_transform) const
{
    return plug::Transform
           {
               parent_transform.getOffset() + m_offset * parent_transform.getScale(),
               m_scale * parent_transform.getScale()
           };
}

