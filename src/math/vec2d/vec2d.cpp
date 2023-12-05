#include <cmath>

#include "math/vec2d.hpp"

plug::Vec2d::Vec2d(const double x_, const double y_) : x(x_), y(y_)
{}

double plug::Vec2d::length2() const
{
    return dot(*this, *this);
}

double plug::Vec2d::length() const
{
    return sqrt(length2());
}

plug::Vec2d &plug::Vec2d::operator += (const plug::Vec2d &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

plug::Vec2d &plug::Vec2d::operator -= (const plug::Vec2d &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

plug::Vec2d &plug::Vec2d::operator *= (const plug::Vec2d &rhs)
{
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

plug::Vec2d &plug::Vec2d::operator /= (const plug::Vec2d &rhs)
{
    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

plug::Vec2d &plug::Vec2d::operator *= (const double val)
{
    x *= val;
    y *= val;

    return *this;
}

plug::Vec2d &plug::Vec2d::operator /= (const double val)
{
    x /= val;
    y /= val;

    return *this;
}

double plug::dot(const plug::Vec2d &lhs, const plug::Vec2d &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double plug::cross(const plug::Vec2d &lhs, const plug::Vec2d &rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

plug::Vec2d normalize(const plug::Vec2d &vec)
{
    double len = vec.length();
    return vec / len;
}

plug::Vec2d operator - (const plug::Vec2d &vec)
{
    plug::Vec2d res(0, 0);
    res -= vec;

    return res;
}

plug::Vec2d operator + (const plug::Vec2d &lhs, const plug::Vec2d &rhs)
{
    plug::Vec2d res = lhs;
    res += rhs;

    return res;
}

plug::Vec2d operator - (const plug::Vec2d &lhs, const plug::Vec2d &rhs)
{
    plug::Vec2d res = lhs;
    res -= rhs;

    return res;
}

plug::Vec2d operator * (const plug::Vec2d &lhs, const plug::Vec2d &rhs)
{
    plug::Vec2d res = lhs;
    res *= rhs;

    return res;
}

plug::Vec2d operator / (const plug::Vec2d &lhs, const plug::Vec2d &rhs)
{
    plug::Vec2d res = lhs;
    res /= rhs;

    return res;
}

plug::Vec2d operator * (const plug::Vec2d &vec, const double val)
{
    plug::Vec2d res = vec;
    res *= val;

    return res;
}

plug::Vec2d operator / (const plug::Vec2d &vec, const double val)
{
    plug::Vec2d res = vec;
    res /= val;

    return res;
}

// plug::Vec2d operator * (const double val, const plug::Vec2d &vec)
// {
//     return operator*(vec, val);
// }

