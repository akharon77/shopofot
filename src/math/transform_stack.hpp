#ifndef MATH_TRANSFORM_STACK_HPP
#define MATH_TRANSFORM_STACK_HPP

#include "util/list.hpp"
#include "plug/math/transform.hpp"

class TransformStack : public plug::TransformStack
{
    List<plug::Transform> m_lst;

public:
    TransformStack();
    TransformStack(const TransformStack &rhs)              = delete;
    TransformStack& operator = (const TransformStack &rhs) = delete;

    ~TransformStack() = default;

    virtual void enter (const plug::Transform &transform) override;
    virtual void leave ()                                 override;

    virtual plug::Transform top() const override;

    virtual plug::Vec2d apply   (const plug::Vec2d &vec) const override;
    virtual plug::Vec2d restore (const plug::Vec2d &vec) const override;
}

#endif  // MATH_TRANSFORM_STACK_HPP

