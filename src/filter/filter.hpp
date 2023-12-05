#ifndef FILTER_FILTER_HPP
#define FILTER_FILTER_HPP

#include <cstddef>
#include "filter/filter_mask.hpp"
#include "plugin.hpp"

class CanvasView;

class Filter : public Plugin
{
public:
    virtual void applyFilter(CanvasView &canvas, const FilterMask &mask) = 0;
};

#endif  // FILTER_FILTER_HPP

