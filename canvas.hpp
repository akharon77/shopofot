#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "widget.hpp"
#include "filter_mask.hpp"
#include "filter_palette.hpp"
#include "tool_palette.hpp"

class Canvas : public Widget
{
    float m_width;
    float m_height;

    sf::VertexArray   m_vertex_arr;

    void updateVertexArray();

public:
    int32_t m_canv_width;
    int32_t m_canv_height;

    ToolPalette   *m_tool_palette;

    FilterMask     m_filter_mask;
    FilterPalette *m_filter_palette;

    sf::RenderTexture m_canv_texture;
    sf::Image         m_image;

    Vec2d m_last_mouse_pos;

    Canvas(const LayoutBox &box, int32_t canv_width, int32_t canv_height, ToolPalette &tool_palette, FilterPalette &filter_palette);

    ~Canvas() = default;
    Canvas& operator = (const Canvas &rhs) = delete;
    Canvas(const Canvas &rhs) = delete;

    sf::Image getImage();
    void loadFromImage(const sf::Image &image);
    void drawImage(const sf::Image &image);
    void resize(uint32_t width, uint32_t height);

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

