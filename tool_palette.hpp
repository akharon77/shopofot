#ifndef TOOL_PALETTE_HPP
#define TOOL_PALETTE_HPP

#include "list.hpp"
#include "tool.hpp"

struct ToolPalette
{
    int32_t m_anch;

    List<Tool*> m_list;

    sf::Color m_foreground_color;
    sf::Color m_background_color;

    Tool *getActiveTool()
    {
        return m_list.Get(m_anch)->val;
    }

    void setActiveTool(int32_t id)
    {
        m_anch = id;
    }

    int32_t addTool(Tool *tool)
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

#endif  // TOOL_PALETTE_HPP

