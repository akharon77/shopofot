#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "widget.hpp"

class ToolPalette;

class Canvas : public Widget
{
    float m_width;
    float m_height;

    sf::VertexArray   m_vertex_arr;

public:
    int32_t m_canv_width;
    int32_t m_canv_height;

    ToolPalette *m_tool_palette;

    sf::RenderTexture m_canv_texture;

    Vector2f m_last_mouse_pos;

    Canvas(Vector2f pos, float width, float height, int32_t canv_width, int32_t canv_height, ToolPalette &tool_palette);

    ~Canvas() = default;
    Canvas& operator = (const Canvas &rhs) = delete;
    Canvas(const Canvas &rhs) = delete;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onResize(float width, float height) override;

    virtual bool onTime (float d_seconds) override;
};

enum class MouseType
{
    PRESSED,
    RELEASED
};

class Tool
{
public:
    virtual void onMainButton(MouseType key, Vector2f pos, Canvas &canvas)      = 0;
    virtual void onSecondaryButton(MouseType key, Vector2f pos, Canvas &canvas) = 0;

    virtual void onModifier1(MouseType key, Vector2f pos, Canvas &canvas) = 0;
    virtual void onModifier2(MouseType key, Vector2f pos, Canvas &canvas) = 0;
    virtual void onModifier3(MouseType key, Vector2f pos, Canvas &canvas) = 0;

    virtual void onMove(Vector2f pos, Canvas &canvas)    = 0;
    virtual void onConfirm(Vector2f pos, Canvas &canvas) = 0;
    virtual void onCancel(Vector2f pos, Canvas &canvas)  = 0;

    virtual Widget* getWidget() = 0;
};

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

    void addTool(Tool *tool)
    {
        m_anch = m_list.PushBack(tool);
    }

    void nextTool()
    {
        m_anch = m_list.Get(m_anch)->next;
        if (m_anch == m_list.m_dummy_head)
            m_anch = m_list.Get(m_anch)->next;
    }
};

#endif  // CANVAS_HPP

