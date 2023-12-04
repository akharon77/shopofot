#include "math/vec2d.hpp"

Vec2d::Vec2d(const double x_, const double y_) : x(x_), y(y_)
{}

Vec2d::Vec2d(const Vector2f &rhs) :
    x(rhs.x),
    y(rhs.y)
{}

Vec2d::operator Vector2f() const
{
    return Vector2f(x, y);
}

double Vec2d::length2() const
{
    return dot(*this, *this);
}

double Vec2d::length() const
{
    return sqrt(length2());
}

Vec2d &Vec2d::operator += (const Vec2d &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

Vec2d &Vec2d::operator -= (const Vec2d &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

Vec2d &Vec2d::operator *= (const Vec2d &rhs)
{
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

Vec2d &Vec2d::operator /= (const Vec2d &rhs)
{
    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

Vec2d &Vec2d::operator *= (const double val)
{
    x *= val;
    y *= val;

    return *this;
}

Vec2d &Vec2d::operator /= (const double val)
{
    x /= val;
    y /= val;

    return *this;
}

double dot(const Vec2d &lhs, const Vec2d &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double cross(const Vec2d &lhs, const Vec2d &rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

Vec2d normalize(const Vec2d &vec)
{
    double len = vec.length();
    return vec / len;
}

Vec2d operator - (const Vec2d &vec)
{
    Vec2d res(0, 0);
    res -= vec;

    return res;
}

Vec2d operator + (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res += rhs;

    return res;
}

Vec2d operator - (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res -= rhs;

    return res;
}

Vec2d operator * (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res *= rhs;

    return res;
}

Vec2d operator / (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res /= rhs;

    return res;
}

Vec2d operator * (const Vec2d &vec, const double val)
{
    Vec2d res = vec;
    res *= val;

    return res;
}

Vec2d operator / (const Vec2d &vec, const double val)
{
    Vec2d res = vec;
    res /= val;

    return res;
}

Vec2d operator * (const double val, const Vec2d &vec)
{
    return vec * val;
}

