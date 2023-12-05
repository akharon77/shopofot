#ifndef PLUG_EVENT_EHC_HPP
#define PLUG_EVENT_EHC_HPP

#include "plug/math.hpp"

namespace plug
{
    struct EHC
    {
        TransformStack &stack;

        bool stopped;
        bool overlapped;
    };
} // namespace plug

#endif // PLUG_EVENT_EHC_HPP

