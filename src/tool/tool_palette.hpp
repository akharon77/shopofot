#ifndef TOOL_TOOL_PALETTE_HPP
#define TOOL_TOOL_PALETTE_HPP

#include "util/list.hpp"
#include "plug/tool.hpp"

struct ToolPalette
{
    int32_t m_anch;

    List<plug::Tool*> m_list;

    int32_t loadPlugin(const char *path);

    plug::Tool *getActiveTool()
    {
        if (m_list.GetSize() == 0)
            return nullptr;

        return m_list.Get(m_anch)->val;
    }

    void setActiveTool(int32_t id)
    {
        m_anch = id;
    }

    int32_t addTool(plug::Tool *tool)
    {
        m_anch = m_list.PushBack(tool);
        return m_anch;
    }

    void nextTool()
    {
        m_anch = m_list.Get(m_anch)->next;
        if (m_anch == m_list.m_dummy_head)
            m_anch = m_list.Get(m_anch)->next;
    }
};

#endif  // TOOL_TOOL_PALETTE_HPP

