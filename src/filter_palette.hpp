#ifndef FILTER_FILTER_PALETTE_HPP
#define FILTER_FILTER_PALETTE_HPP

#include "util/list.hpp"
#include "plug/filter.hpp"

class FilterPalette
{
    List<plug::Filter*> m_filter_lst;
    plug::Filter *m_last_filter;

public:
    size_t addFilter(plug::Filter &filter);

    plug::Filter* getFilter    (size_t filter_id);
    plug::Filter* getLastFilter();

    void setLastFilter(size_t filter_id);

    size_t getFilterCount() const;

    int32_t loadPlugin(plug::Plugin *plugin);
};

#endif  // FILTER_FILTER_PALETTE_HPP

