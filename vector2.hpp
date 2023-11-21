#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

const double EPS = 1e-6;

class Vec2d
{
public:
    explicit Vec2d(const double x = 0, const double y = 0);

    ~Vec2d()                             = default;
    Vec2d(const Vec2d &rhs)              = default;
    Vec2d &operator = (const Vec2d &rhs) = default;

    double x, y;

    double length();
    double length2();

    Vec2d &operator /= (const double val);
    Vec2d &operator += (const Vec2d &rhs);
    Vec2d &operator -= (const Vec2d &rhs);
    Vec2d &operator *= (const double val);
    Vec2d &operator *= (const Vec2d &rhs);
    Vec2d &operator /= (const Vec2d &rhs);
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

#endif  // VECTOR2D_HPP

