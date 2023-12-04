#ifndef LINE_EDIT_TOOL_HPP
#define LINE_EDIT_TOOL_HPP

#include "line_edit.hpp"
#include "tool.hpp"

class LineEditTool : public Tool
{
    LineEdit m_widget;

    enum class status_t
    {
        DEFAULT,
        ACTIVE
    };

    status_t m_status;

public:
    LineEditTool(sf::Font &font, float thickness) :
        m_widget({0, 0}, 0, 0, font, thickness),
        m_status(status_t::DEFAULT)
    {}

    virtual void onMainButton(MouseType key, Vector2f pos, Canvas &canvas) override;

    virtual void onSecondaryButton(MouseType key, Vector2f pos, Canvas &canvas) {}

    virtual void onModifier1(MouseType key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier2(MouseType key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier3(MouseType key, Vector2f pos, Canvas &canvas) {}

    virtual void onMove(Vector2f pos, Canvas &canvas) {}

    virtual void onConfirm(Vector2f pos, Canvas &canvas) override;
    virtual void onCancel(Vector2f pos, Canvas &canvas) override;

    virtual Widget* getWidget()
    {
        if (m_status == status_t::ACTIVE)
            return &m_widget;

        return nullptr;
    }
};

#endif  // LINE_EDIT_TOOL_HPP

