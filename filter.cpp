#include <cassert>
#include <dlfcn.h>

#include "filter.hpp"
#include "filter_mask.hpp"
#include "filter_palette.hpp"

FilterMask::FilterMask(size_t width, size_t height) :
    m_width(width),
    m_height(height)
{
    m_buf = new bool[width * height];
    assert(m_buf != nullptr && "m_buf is nullptr");
    
    fill(true);
}

FilterMask::~FilterMask()
{
    assert(m_buf != nullptr && "m_buf is nullptr");

    delete[] m_buf;
    m_buf = nullptr;
}

void FilterMask::resize(size_t width, size_t height)
{
    m_width = width;
    m_height = height;

    delete[] m_buf;
    m_buf = new bool[width * height];

    fill(true);
}

size_t FilterMask::getWidth() const
{
    return m_width;
}

size_t FilterMask::getHeight() const
{
    return m_height;
}

bool FilterMask::getPixel(size_t x, size_t y) const
{
    return m_buf[y * m_width + x];
}

void FilterMask::setPixel(size_t x, size_t y, bool value)
{
    m_buf[y * m_width + x] = value;
}

void FilterMask::fill(bool value)
{
    for (int32_t i = 0; i < m_width * m_height; ++i)
        m_buf[i] = value;
}

void FilterMask::invert()
{
    for (int32_t i = 0; i < m_width * m_height; ++i)
        m_buf[i] = !m_buf[i];
}

size_t FilterPalette::addFilter(Filter &filter)
{
    m_last_filter = &filter;
    return m_filter_lst.PushBack(&filter);
}

Filter* FilterPalette::getFilter(size_t filter_id)
{
    return m_filter_lst.Get(filter_id)->val;
}

Filter* FilterPalette::getLastFilter()
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

    typedef Filter* plugin_loader_t(void);
    plugin_loader_t *load = (plugin_loader_t*) loadPlugin_symbol;
    Filter *loaded_filter = load();

    int32_t res = addFilter(*loaded_filter);

    dlclose(plugin);

    return res;
}

