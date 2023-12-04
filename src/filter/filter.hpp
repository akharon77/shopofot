#ifndef FILTER_HPP
#define FILTER_HPP

#include <cstddef>
#include "filter_mask.hpp"
#include "plugin.hpp"

class Canvas;

class Filter : public Plugin
{
public:
    virtual void applyFilter(Canvas &canvas, const FilterMask &mask) = 0;
};

#endif  // FILTER_HPP

