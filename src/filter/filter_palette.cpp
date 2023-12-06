#include <cassert>
#include <dlfcn.h>

#include "filter_palette.hpp"

size_t FilterPalette::addFilter(plug::Filter &filter)
{
    m_last_filter = &filter;
    return m_filter_lst.PushBack(&filter);
}

plug::Filter* FilterPalette::getFilter(size_t filter_id)
{
    return m_filter_lst.Get(filter_id)->val;
}

plug::Filter* FilterPalette::getLastFilter()
{
    return m_last_filter;
}

void FilterPalette::setLastFilter(size_t filter_id)
{
    m_last_filter = getFilter(filter_id);
}

size_t FilterPalette::getFilterCount() const
{
    return m_filter_lst.GetSize();
}

int32_t FilterPalette::loadPlugin(const char *path)
{
    void *plugin = dlopen(path, RTLD_NOW | RTLD_LOCAL | RTLD_NODELETE);
    void *loadPlugin_symbol = dlsym(plugin, "loadPlugin");

    typedef plug::Filter* plugin_loader_t(void);
    plugin_loader_t *load = (plugin_loader_t*) loadPlugin_symbol;
    plug::Filter *loaded_filter = load();

    int32_t res = addFilter(*loaded_filter);

    dlclose(plugin);

    return res;
}

