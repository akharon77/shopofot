#include <cassert>
#include <dlfcn.h>

#include "tool/tool_palette.hpp"

int32_t ToolPalette::loadPlugin(const char *path)
{
    void *plugin = dlopen(path, RTLD_NOW | RTLD_LOCAL | RTLD_NODELETE);
    void *loadPlugin_symbol = dlsym(plugin, "loadPlugin");

    typedef plug::Tool* plugin_loader_t(void);
    plugin_loader_t *load = (plugin_loader_t*) loadPlugin_symbol;
    plug::Tool *loaded_tool = load();

    int32_t res = addTool(loaded_tool);

    dlclose(plugin);

    return res;
}

