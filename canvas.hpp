#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "widget.hpp"

class Canvas : public Widget
{
    enum status_t
    {
        DEFAULT,
        TOOL_DOWN
    };

    status_t m_status;

    float m_width;
    float m_height;

    int32_t m_canv_width;
    int32_t m_canv_height;

    sf::RenderTexture m_canv_texture;
    sf::VertexArray   m_vertex_arr;

public:
    Canvas(Vector2f pos, float width, float height, int32_t canv_width, int32_t canv_height);

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

#endif  // CANVAS_HPP

