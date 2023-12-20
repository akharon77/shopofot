#ifndef PLUGIN_LOADER_HPP
#define PLUGIN_LOADER_HPP

#include "plug/plugin.hpp"
#include "filter_palette.hpp"
#include "tool/tool_palette.hpp"
#include "shopofot.hpp"

void loadPlugins(const char *path, FilterVerticalButtonList &filter_palette, ToolVerticalButtonList &tool_palette);

#endif  // PLUGIN_LOADER_HPP

