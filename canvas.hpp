#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "widget.hpp"

class Tool;

class Canvas : public Widget
{
    float m_width;
    float m_height;

    sf::VertexArray   m_vertex_arr;

public:
    int32_t m_canv_width;
    int32_t m_canv_height;

    Tool *m_tool;

    sf::RenderTexture m_canv_texture;

    Canvas(Vector2f pos, float width, float height, int32_t canv_width, int32_t canv_height, Tool *tool);

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
    Tool *m_active_tool;

    sf::Color m_foreground_color;
    sf::Color m_background_color;
};

#endif  // CANVAS_HPP

