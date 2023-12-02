#ifndef BRUSH_TOOL_HPP
#define BRUSH_TOOL_HPP

#include "tool.hpp"
#include "universal_layout_box.hpp"

class BrushToolWidget : public Widget
{
    sf::CircleShape m_shape;

public:
    BrushToolWidget() :
        Widget(UniversalLayoutBox(0_px, 0_px)),
        m_shape(2)
    {
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setOrigin(1, 1);
        m_shape.setRadius(5);
    }

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;
    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}

    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) {}

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) {}

    virtual bool onKeyboardPressed  (KeyboardKey key) {}
    virtual bool onKeyboardReleased (KeyboardKey key) {}

    virtual bool onTime (float d_seconds) {}

    virtual bool onResize(float width, float height) {}
};

class BrushTool : public Tool
{
    enum status_t
    {
        DEFAULT,
        HOLD
    };

    status_t m_status;
    Vec2d m_prev_pos;

    BrushToolWidget m_widget;

public:
    BrushTool() :
        m_status(DEFAULT)
    {}

    virtual void onMainButton(MouseType key, Vector2f pos, Canvas &canvas) override;

    virtual void onSecondaryButton(MouseType key, Vector2f pos, Canvas &canvas) {}

    virtual void onModifier1(MouseType key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier2(MouseType key, Vector2f pos, Canvas &canvas) {}
    virtual void onModifier3(MouseType key, Vector2f pos, Canvas &canvas) {}

    virtual void onMove(Vector2f pos, Canvas &canvas) override;

    virtual void onConfirm(Vector2f pos, Canvas &canvas) {}
    virtual void onCancel(Vector2f pos, Canvas &canvas) {}

    virtual Widget* getWidget()
    {
        return &m_widget;
    }
};

#endif  // BRUSH_TOOL_HPP

