#ifndef LINE_TOOL_HPP
#define LINE_TOOL_HPP

#include "tool.hpp"

class LineToolWidget : public Widget
{
public:
    enum status_t
    {
        DEFAULT,
        HOLD
    };

    status_t m_status;

    Vector2f m_first_pos;
    Vector2f m_second_pos;

    LineToolWidget() :
        Widget(),
        m_status(DEFAULT)
    {}

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;
    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
    {
        if (m_status == HOLD)
        {
            Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
            m_first_pos = top_transf.applyTransform({x, y});
        }
    }

    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
    {
        m_status = DEFAULT;
    }

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list)
    {
        if (m_status == HOLD)
        {
            Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
            m_second_pos = top_transf.applyTransform({x, y});
        }
    }

    virtual bool onKeyboardPressed  (KeyboardKey key) {}
    virtual bool onKeyboardReleased (KeyboardKey key) {}

    virtual bool onTime (float d_seconds) {}

    virtual bool onResize(float width, float height) {}
};

class LineTool : public Tool
{
    LineToolWidget m_widget;

public:
    LineTool() {}
    ~LineTool() {}

    virtual void onMainButton(MouseKey key, Vector2f pos, Canvas &canvas) override;

    virtual void onSecondaryButton(MouseKey key, Vector2f pos, Canvas &canvas) {}

    virtual void onModifier1(MouseKey key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier2(MouseKey key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier3(MouseKey key, Vector2f pos, Canvas &canvas) {}

    virtual void onMove(Vector2f pos, Canvas &canvas) {}

    virtual void onConfirm(Vector2f pos, Canvas &canvas) {}
    virtual void onCancel(Vector2f pos, Canvas &canvas) {}

    virtual Widget* getWidget()
    {
        return &m_widget;
    }
};

#endif  // LINE_TOOL_HPP

