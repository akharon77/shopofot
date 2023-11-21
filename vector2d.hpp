#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

// compatibility
using Vector2f = sf::Vector2f;
float dot(const Vector2f &lhs, const Vector2f &rhs);
float len2(const Vector2f &rhs);
float len(const Vector2f &rhs);

class Vec2d
{
public:
    double x, y;

    double length();
    double length2();
};

double dot   (const Vec2d &lhs, const Vec2d &rhs);
double cross (const Vec2d &lhs, const Vec2d &rhs);

Vec2d normalize (const Vec2d &vec);

Vec2d operator + (const Vec2d &lhs, const Vec2d &rhs);
Vec2d operator - (const Vec2d &lhs, const Vec2d &rhs);

Vec2d operator * (const Vec2d &vec, const double val);
Vec2d operator * (const double val, const Vec2d &vec);

Vec2d operator - (const Vec2d &vec);
Vec2d operator / (const Vec2d &lhs, const Vec2d &rhs);

Vec2d &operator /= (Vec2d &lhs, const double val);
Vec2d &operator += (Vec2d &lhs, const Vec2d &rhs);
Vec2d &operator -= (Vec2d &lhs, const Vec2d &rhs);
Vec2d &operator *= (Vec2d &lhs, const double val);
Vec2d &operator *= (Vec2d &lhs, const Vec2d &rhs);
Vec2d &operator /= (Vec2d &lhs, const Vec2d &rhs);

const double EPS = 1e-6;

#endif  // VECTOR2_HPP

