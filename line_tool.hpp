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
        m_status(DEFAULT)
    {}

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;
    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}

    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) {}

    virtual bool onKeyboardPressed  (KeyboardKey key) {}
    virtual bool onKeyboardReleased (KeyboardKey key) {}

    virtual bool onTime (float d_seconds) {}

    virtual bool onResize(float width, float height) {}
};

class LineTool : public Tool
{
    LineToolWidget m_widget;

public:
    virtual void onMainButton(MouseType key, Vector2f pos, Canvas &canvas) override;

    virtual void onSecondaryButton(MouseType key, Vector2f pos, Canvas &canvas) {}

    virtual void onModifier1(MouseType key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier2(MouseType key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier3(MouseType key, Vector2f pos, Canvas &canvas) {}

    virtual void onMove(Vector2f pos, Canvas &canvas) override;

    virtual void onConfirm(Vector2f pos, Canvas &canvas) override;
    virtual void onCancel(Vector2f pos, Canvas &canvas) override;

    virtual Widget* getWidget()
    {
        return &m_widget;
    }
};

#endif  // LINE_TOOL_HPP

