#ifndef MATH_TRANSFORM_STACK_HPP
#define MATH_TRANSFORM_STACK_HPP

#include "list.hpp"
#include "math/transform.hpp"

class TransformStack : public plug::TransformStack
{
    List<Transform> m_lst;

public:
    TransformStack();
    TransformStack(const TransformStack &rhs)              = delete;
    TransformStack& operator = (const TransformStack &rhs) = delete;

    ~TransformStack() = default;

    virtual void enter (const Transform &transform) override;
    virtual void leave ()                           override;

    virtual Transform top() const override;

    virtual Vec2d apply   (const Vec2d &vec) const override;
    virtual Vec2d restore (const Vec2d &vec) const override;
}

#endif  // MATH_TRANSFORM_STACK_HPP

