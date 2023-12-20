#ifndef UI_CANVAS_VIEW_MANAGER_HPP
#define UI_CANVAS_VIEW_MANAGER_HPP

#include "util/list.hpp"
#include "widget.hpp"
#include "ui/button/button.hpp"
#include "ui/canvas_view.hpp"
#include "ui/scrollbar.hpp"
#include "ui/frame.hpp"

struct CanvasViewManagerTexture
{
    ScrollBarTexture *m_scrollbar_texture;
    FrameTexture     *m_frame_texture;
};

class CanvasViewManager : public Widget, public Container
{
public:
    struct CanvasWindow
    {
        CanvasView *m_canvas;
        ScrollBar  *m_scrollbar;
        Frame      *m_frame;

        ~CanvasWindow();
    };

    FilterPalette *m_filter_palette;
    ToolPalette   *m_tool_palette;
    plug::ColorPalette *m_color_palette;
    
    CanvasViewManagerTexture *m_texture;

    List<CanvasWindow*> m_canv_window_lst;
    int32_t m_glob_cnt;

    CanvasViewManager(const plug::LayoutBox &box, ToolPalette &tool_palette, FilterPalette &filter_palette, plug::ColorPalette &color_palette, CanvasViewManagerTexture &canv_manager_texture);

    ~CanvasViewManager() = default;
    CanvasViewManager& operator = (const CanvasViewManager &rhs) = delete;
    CanvasViewManager(const CanvasViewManager &rhs) = delete;

    void addCanvas(int32_t canv_width, int32_t canv_height);
    CanvasView *getActive();
    FilterPalette *getFilterPalette();
    ToolPalette *getToolPalette();

    virtual bool close(int32_t id) override;

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual void onTime(double d_seconds, plug::EHC &context) override;

    virtual void onMouseMoved (double x, double y, plug::EHC &context) override;

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
    virtual void onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) override;

    virtual void onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) override;
    virtual void onKeyboardReleased (plug::KeyCode key, plug::EHC &context) override;

    virtual void onResize(double width, double height, plug::EHC &context) override;
};

#endif  // UI_CANVAS_MANAGER_HPP

