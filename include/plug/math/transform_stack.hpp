#ifndef PLUG_MATH_TRANSFORM_STACK_HPP
#define PLUG_MATH_TRANSFORM_STACK_HPP

#include "plug/math/transform.hpp"
#include "plug/math/vec2d.hpp"

namespace plug
{
    class TransformStack
    {
        public:
            TransformStack() {}

            virtual ~TransformStack() {}

            virtual void enter (const Transform &transform) = 0;
            virtual void leave ()                           = 0;

            virtual Transform top() const = 0;

            virtual Vec2d apply   (const Vec2d &vec) const = 0;
            virtual Vec2d restore (const Vec2d &vec) const = 0;
    };
} // namespace plug

#endif  // PLUG_MATH_TRANSFORM_STACK_HPP

