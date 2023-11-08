#include "line_edit_tool.hpp"
#include "canvas.hpp"

void LineEditTool::onMainButton(MouseType key, Vector2f pos, Canvas &canvas)
{
    m_status = status_t::ACTIVE;
    m_widget.m_transf.m_offset = pos;
}

void LineEditTool::onConfirm(Vector2f pos, Canvas &canvas)
{
    m_status = status_t::DEFAULT;
    m_widget.m_text.setCharacterSize(m_widget.m_thickness * canvas.m_canv_height);
    m_widget.draw(canvas.m_canv_texture, {m_widget.m_transf.m_offset.x * canvas.m_canv_width, m_widget.m_transf.m_offset.y * canvas.m_canv_height});
    m_widget.clear();
}

void LineEditTool::onCancel(Vector2f pos, Canvas &canvas)
{
    m_status = status_t::DEFAULT;
    m_widget.clear();
}

