#include <cmath>

#include "vector2d.hpp"

explicit Vec2d::Vec2d(const double x_, const double y_) : x(x_), y(y_)
{}

double Vec2d::length2() const
{
    return dot(*this, *this);
}

double Vec2d::length() const
{
    return sqrt(length2());
}

Vec2d &operator += (const Vec2d &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

Vec2d &operator -= (const Vec2d &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

Vec2d &operator *= (const Vec2d &rhs)
{
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

Vec2d &operator /= (const Vec2d &rhs)
{
    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

Vec2d &operator *= (const double val)
{
    x *= val;
    y *= val;

    return *this;
}

Vec2d &operator /= (const double val)
{
    x /= val;
    y /= val;

    return *this;
}

inline double dot(const Vec2d &lhs, const Vec2d &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

inline double cross(const Vec2d &lhs, const Vec2d &rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

inline Vec2d normalize(const Vec2d &vec)
{
    double len = vec.length();
    return vec / len;
}

inline Vec2d operator + (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res += rhs;

    return res;
}

inline Vec2d operator - (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res -= rhs;

    return res;
}

inline Vec2d operator * (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res *= rhs;

    return res;
}

inline Vec2d operator / (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res /= rhs;

    return res;
}

inline Vec2d operator * (const Vec2d &vec, const double val)
{
    Vec2d res = vec;
    res *= val;

    return res;
}

inline Vec2d operator / (const Vec2d &vec, const double val)
{
    Vec2d res = vec;
    res /= val;

    return res;
}

inline Vec2d operator * (const double val, const Vec2d &vec)
{
    return vec * val;
}

#endif
