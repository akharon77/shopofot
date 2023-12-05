#ifndef FILTER_FILTER_PALETTE_HPP
#define FILTER_FILTER_PALETTE_HPP

#include "util/list.hpp"
#include "filter/filter.hpp"

class FilterPalette
{
    List<Filter*> m_filter_lst;
    Filter *m_last_filter;

public:
    size_t addFilter(Filter &filter);

    Filter* getFilter    (size_t filter_id);
    Filter* getLastFilter();

    void setLastFilter(size_t filter_id);

    size_t getFilterCount() const;

    int32_t loadPlugin(const char *path);
};

#endif  // FILTER_FILTER_PALETTE_HPP

