#ifndef BLACKWHITE_FILTER_HPP
#define BLACKWHITE_FILTER_HPP

#include "filter.hpp"

class BlackWhiteFilter : public Filter
{
public:
    BlackWhiteFilter() {}
    virtual void applyFilter(Canvas &canvas, const FilterMask &mask) override;
};

#endif  // BLACKWHITE_FILTER_HPP

