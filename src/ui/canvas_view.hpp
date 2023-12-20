#ifndef UI_CANVAS_VIEW_HPP
#define UI_CANVAS_VIEW_HPP

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "widget.hpp"
#include "canvas.hpp"
#include "tool/tool_palette.hpp"
#include "graphics/render_texture.hpp"
#include "filter_palette.hpp"

class CanvasView : public Widget
{
public:
    Canvas *m_canvas;

    ToolPalette   *m_tool_palette;
    FilterPalette *m_filter_palette;
    plug::ColorPalette *m_color_palette;

    plug::Vec2d m_last_mouse_pos;

    bool m_active;

    CanvasView(const plug::LayoutBox &box, int32_t canv_width, int32_t canv_height, ToolPalette &tool_palette, FilterPalette &filter_palette, plug::ColorPalette &color_palette);

    ~CanvasView() = default;
    CanvasView& operator = (const CanvasView &rhs) = delete;
    CanvasView(const CanvasView &rhs) = delete;

    void loadFromImage(const char *path);

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

