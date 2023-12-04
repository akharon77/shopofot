#ifndef POLYGON_TOOL_HPP
#define POLYGON_TOOL_HPP

#include "tool.hpp"
#include "universal_layout_box.hpp"

class PolygonToolWidget : public Widget
{
public:
    enum status_t
    {
        DEFAULT,
        ACTIVE
    };

    status_t m_status;

    sf::VertexArray m_arr;
    Vec2d m_pos;

    PolygonToolWidget() :
        Widget(UniversalLayoutBox(0_px, 0_px)),
        m_arr(sf::LineStrip),
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

class PolygonTool : public Tool
{
    PolygonToolWidget m_widget;

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

#endif  // POLYGON_TOOL_HPP

