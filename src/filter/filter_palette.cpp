#include <cassert>
#include <dlfcn.h>

#include "filter_palette.hpp"

size_t FilterPalette::addFilter(plug::Filter &filter)
{
    m_last_filter = &filter;
    m_anch = m_filter_lst.PushBack(&filter);
    return m_anch;
}

plug::Filter* FilterPalette::getFilter(size_t filter_id)
{
    return m_filter_lst.Get(filter_id)->val;
}

plug::Filter* FilterPalette::getLastFilter()
{
    return getFilter(m_anch);
}

void FilterPalette::setLastFilter(size_t filter_id)
{
    m_last_filter = getFilter(filter_id);
    m_anch = filter_id;
}

size_t FilterPalette::getFilterCount() const
{
    return m_filter_lst.GetSize();
}

int32_t FilterPalette::loadPlugin(plug::Plugin *plugin)
{
    plug::Filter *filter = static_cast<plug::Filter*>(
            plugin->tryGetInterface(static_cast<size_t>(
                    plug::PluginGuid::Filter)));

    if (filter)
        return addFilter(*filter);

    return -1;
}

