#include "transform.hpp"

Transform::Transform(const Vector2f &offset, const Vector2f &scale) :
    m_offset (offset),
    m_scale  (scale)
{}

Transform Transform::applyParent(const Transform &par) const
{
    return Transform
    {
        par.m_offset + Vector2f{par.m_scale.x * m_offset.x, par.m_scale.y * m_offset.y},
        {
            m_scale.x * par.m_scale.x,
            m_scale.y * par.m_scale.y
        }
    };
}

Vector2f Transform::applyTransform(const Vector2f &vec) const
{
    Vector2f res = vec - m_offset;
    res.x /= m_scale.x;
    res.y /= m_scale.y;

    return res;
}
