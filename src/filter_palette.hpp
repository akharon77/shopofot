#ifndef FILTER_FILTER_PALETTE_HPP
#define FILTER_FILTER_PALETTE_HPP

#include "util/list.hpp"
#include "plug/filter.hpp"

class FilterPalette
{
    List<plug::Filter*> m_filter_lst;
    plug::Filter *m_last_filter;

    int32_t m_anch;

public:
    size_t addFilter(plug::Filter &filter);

    plug::Filter* getFilter    (size_t filter_id);
    plug::Filter* getLastFilter();

    void setLastFilter(size_t filter_id);

    size_t getFilterCount() const;

    int32_t loadPlugin(plug::Plugin *plugin);

    void nextFilter()
    {
        m_anch = m_filter_lst.Get(m_anch)->next;
        if (m_anch == m_filter_lst.m_dummy_head)
            m_anch = m_filter_lst.Get(m_anch)->next;

        setLastFilter(m_anch);
    }
};

#endif  // FILTER_FILTER_PALETTE_HPP

