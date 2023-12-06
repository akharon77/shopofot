#ifndef UI_CANVAS_VIEW_HPP
#define UI_CANVAS_VIEW_HPP

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "widget.hpp"
#include "filter/filter_mask.hpp"
#include "filter/filter_palette.hpp"
#include "tool/tool_palette.hpp"
#include "graphics/render_texture.hpp"

class CanvasView : public Widget
{
    plug::VertexArray m_vertex_arr;

    void updateVertexArray();

public:
    int32_t m_canv_width;
    int32_t m_canv_height;

    ToolPalette   *m_tool_palette;

    FilterMask     m_filter_mask;
    FilterPalette *m_filter_palette;

    sf::RenderTexture m_sf_canv_texture;
    RenderTexture     m_canv_texture;

    sf::Image           m_image;

    plug::Vec2d m_last_mouse_pos;

    CanvasView(const plug::LayoutBox &box, int32_t canv_width, int32_t canv_height, ToolPalette &tool_palette, FilterPalette &filter_palette);

    ~CanvasView() = default;
    CanvasView& operator = (const CanvasView &rhs) = delete;
    CanvasView(const CanvasView &rhs) = delete;

    sf::Image getImage();
    void loadFromImage(const sf::Image &image);
    void drawImage(const sf::Image &image);

    void resize(uint32_t width, uint32_t height);

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;
    
    virtual void onTime(double d_seconds, plug::EHC &context) override;

    virtual void onMouseMoved (double x, double y, plug::EHC &context) override;

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
    virtual void onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) override;

    virtual void onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) override;
    virtual void onKeyboardReleased (plug::KeyCode key, plug::EHC &context) override;

    virtual void onResize(double width, double height, plug::EHC &context) override;
};

#endif  // UI_CANVAS_VIEW_HPP

