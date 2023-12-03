#ifndef CANVAS_MANAGER_HPP
#define CANVAS_MANAGER_HPP

#include "list.hpp"
#include "widget.hpp"
#include "button.hpp"
#include "canvas.hpp"
#include "scrollbar.hpp"
#include "frame.hpp"

struct CanvasManagerTexture
{
    ScrollBarTexture *m_scrollbar_texture;
    FrameTexture     *m_frame_texture;
};

class CanvasManager : public Widget, public Container
{
    struct CanvasWindow
    {
        Canvas    *m_canvas;
        ScrollBar *m_scrollbar;
        Frame     *m_frame;

        ~CanvasWindow();
    };

    FilterPalette *m_filter_palette;
    ToolPalette   *m_tool_palette;
    
    CanvasManagerTexture *m_texture;

    List<CanvasWindow*> m_canv_window_lst;

public:
    CanvasManager(const LayoutBox &box, ToolPalette &tool_palette, FilterPalette &filter_palette, CanvasManagerTexture &canv_manager_texture);

    ~CanvasManager() = default;
    CanvasManager& operator = (const CanvasManager &rhs) = delete;
    CanvasManager(const CanvasManager &rhs) = delete;

    void addCanvas(int32_t canv_width, int32_t canv_height);
    Canvas *getActive();
    FilterPalette *getFilterPalette();
    ToolPalette *getToolPalette();

    virtual bool close(int32_t id) override;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onTime (float d_seconds) override;

    virtual bool onResize(float width, float height) override;
};

#endif  // CANVAS_MANAGER_HPP

