#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include "ui/button.hpp"
#include "tool/tool_palette.hpp"
#include "ui/canvas_view.hpp"

class ToolButton : public ToggleButton
{
    ToolPalette *m_tool_palette;
    int32_t m_tool_id;

public:
    ToolButton(const plug::LayoutBox &box, ButtonTexture &btn_texture, ToolPalette &tool_palette, int32_t tool_id);

    virtual void onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context) override;
};

class ToolBar : public Widget
{
    ToolPalette *m_tool_palette;

    List<ToolButton*> m_btn_list;

    int32_t m_cnt_x;

    double m_btn_width;
    double m_btn_height;


public:
    int32_t m_toggled_id;
    ToolBar(double btn_width, double btn_height, ToolPalette &tool_palette, int32_t cnt_x);

    ~ToolBar() = default;
    ToolBar& operator = (const ToolBar &rhs) = delete;
    ToolBar(const ToolBar &rhs) = delete;

    void setToggled(int32_t id);
    void addButton(ButtonTexture &btn_texture, int32_t tool_id);

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual void onTime(double d_seconds, plug::EHC &context) {}

    virtual void onMouseMoved (double x, double y, plug::EHC &context) override;

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
    virtual void onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) override;

    virtual void onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) {}
    virtual void onKeyboardReleased (plug::KeyCode key, plug::EHC &context) {}

    virtual void onResize(double width, double height, plug::EHC &context) {context.stopped = false;}
};


#endif  // TOOLBAR_HPP

