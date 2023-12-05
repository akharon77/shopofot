#include "math/transform_stack.hpp"

TransformStack::TransformStack()
{
    m_lst.PushBack(plug::Transform(plug::Vec2d(0, 0), plug::Vec2d(1, 1)));
}

void TransformStack::enter(const plug::Transform &transform)
{
    plug::Transform curr_top = top();
    m_lst.PushBack(transform.combine(curr_top));
}

void TransformStack::leave()
{
    m_lst.PopBack();
}

plug::Transform TransformStack::top() const
{
    return m_lst.Get(m_lst.GetTail())->val;
}

plug::Vec2d TransformStack::apply(const plug::Vec2d &vec) const
{
    plug::Transform curr_top = top();
    return curr_top.apply(vec);
}

plug::Vec2d TransformStack::restore(const plug::Vec2d &vec) const
{
    plug::Transform curr_top = top();
    return curr_top.restore(vec);
}

