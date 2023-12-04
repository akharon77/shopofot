#include "math/transform_stack.hpp"

TransformStack::TransformStack() :
    m_lst(0)
{
    m_lst.PushBack(Transform(Vec2d(0, 0), Vec2d(1, 1)));
}

void TransformStack::enter(const TransformStack &transform)
{
    Transform curr_top = top();
    transf_list.PushBack(transform.combine(top));
}

void TransformStack::leave()
{
    m_lst.PopBack();
}

Transform TransformStack::top() const
{
    return m_lst.Get(m_lst.GetTail())->val;
}

Vec2d TransformStack::apply(const Vec2d &vec) const
{
    Transform curr_top = top();
    return curr_top.apply(vec);
}

Vec2d TransformStack::restore(const Vec2d &vec) const
{
    Transform curr_top = top();
    return curr_top.restore(vec);
}

