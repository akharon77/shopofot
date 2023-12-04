#ifndef BRIGHTNESS_FILTER_HPP
#define BRIGHTNESS_FILTER_HPP

#include "filter.hpp"

class BrightnessFilterData : public PluginData
{
public:
    bool m_sign = false;

    virtual const char *getName() const override
    {
        if (m_sign)
            return "Brightness+";
        return "Brightness-";
    }

    virtual const char *getTexturePath() const override
    {
        return nullptr;
    }
};

class BrightnessFilter : public Filter
{
    BrightnessFilterData m_plugin_data;

    int32_t m_ref_cnt;
    float m_delta;

public:
    BrightnessFilter();
    ~BrightnessFilter() = default;

    virtual const PluginData *getPluginData() const override
    {
        return (PluginData*) &m_plugin_data;
    }

    virtual Plugin* tryGetInterface(size_t interface_id) override;

    virtual void addReference() override;

    virtual void release() override;

    void setBrightnessDelta(float delta);

    virtual void applyFilter(Canvas &canvas, const FilterMask &mask) override;
};

extern "C" Plugin *loadPlugin();

#endif  // BRIGHTNESS_FILTER_HPP

