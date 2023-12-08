#include <cassert>
#include "tool/tool_palette.hpp"

int32_t ToolPalette::loadPlugin(plug::Plugin *plugin)
{
    plug::Tool *tool = static_cast<plug::Tool*>(
            plugin->tryGetInterface(static_cast<size_t>(
                    plug::PluginGuid::Tool)));

    if (tool)
        return addTool(tool);

    return -1;
}

