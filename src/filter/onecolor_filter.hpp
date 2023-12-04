#ifndef ONECOLOR_FILTER_HPP
#define ONECOLOR_FILTER_HPP

#include "filter.hpp"

class OneColorFilter : public Filter
{
public:
    enum mask_t : uint8_t
    {
        RED = 1,
        GREEN = 1 << 1,
        BLUE = 1 << 2
    };

    OneColorFilter(uint8_t mask);
    virtual void applyFilter(Canvas &canvas, const FilterMask &mask) override;

private:
    mask_t m_mask;
};

#endif  // ONECOLOR_FILTER_HPP

