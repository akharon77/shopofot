#ifndef PLUGIN_LOADER_HPP
#define PLUGIN_LOADER_HPP

#include "plug/plugin.hpp"
#include "filter_palette.hpp"
#include "tool/tool_palette.hpp"

void loadPlugins(const char *path, FilterPalette &filter_palette, ToolPalette &tool_palette);

#endif  // PLUGIN_LOADER_HPP

