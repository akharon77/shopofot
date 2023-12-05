#ifndef PLUG_MATH_VEC2D_HPP
#define PLUG_MATH_VEC2D_HPP

namespace plug
{
    class Vec2d
    {
    public:
        explicit Vec2d(const double x = 0, const double y = 0);

        ~Vec2d()                             = default;
        Vec2d(const Vec2d &rhs)              = default;
        Vec2d &operator = (const Vec2d &rhs) = default;

        double x, y;

        double length() const;
        double length2() const;

        Vec2d &operator /= (const double val);
        Vec2d &operator += (const Vec2d &rhs);
        Vec2d &operator -= (const Vec2d &rhs);
        Vec2d &operator *= (const double val);
        Vec2d &operator *= (const Vec2d &rhs);
        Vec2d &operator /= (const Vec2d &rhs);

        bool operator == (const Vec2d &rhs) const = default;
    };

    double dot   (const Vec2d &lhs, const Vec2d &rhs);
    double cross (const Vec2d &lhs, const Vec2d &rhs);

    Vec2d normalize (const Vec2d &vec);

    Vec2d operator + (const Vec2d &lhs, const Vec2d &rhs);
    Vec2d operator - (const Vec2d &lhs, const Vec2d &rhs);

    Vec2d operator * (const Vec2d &vec, const double val);
    // Vec2d operator * (const double val, const Vec2d &vec);
    Vec2d operator * (const Vec2d &lhs, const Vec2d &rhs);

    Vec2d operator - (const Vec2d &vec);
    Vec2d operator / (const Vec2d &lhs, const Vec2d &rhs);
    Vec2d operator / (const Vec2d &vec, const double val);
}  // namespace plug

#endif  // PLUG_MATH_VEC2D_HPP

