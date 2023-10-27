#ifndef BRIGHTNESS_FILTER_HPP
#define BRIGHTNESS_FILTER_HPP

#include "filter.hpp"

class BrightnessFilter : public Filter
{
    float m_delta;

public:
    BrightnessFilter() {}
    void setBrightnessDelta(float delta);

    virtual void applyFilter(Canvas &canvas, const FilterMask &mask) override;
};

#endif  // BRIGHTNESS_FILTER_HPP

