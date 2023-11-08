#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include "toggle_button.hpp"
#include "tool_palette.hpp"

class ToolButton : public ToggleButton
{
    ToolPalette *m_tool_palette;
    int32_t m_tool_id;

public:
    ToolButton(Vector2f pos, float width, float height, ButtonTexture &btn_texture, ToolPalette &tool_palette, int32_t tool_id);

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
};

class ToolBar : public Widget
{
    ToolPalette *m_tool_palette;

    List<ToolButton*> m_btn_list;

    int32_t m_cnt_x;

    float m_btn_width;
    float m_btn_height;


public:
    int32_t m_toggled_id;
    ToolBar(Vector2f pos, float btn_width, float btn_height, ToolPalette &tool_palette, int32_t cnt_x);

    ~ToolBar() = default;
    ToolBar& operator = (const ToolBar &rhs) = delete;
    ToolBar(const ToolBar &rhs) = delete;

    void setToggled(int32_t id);
    void addButton(ButtonTexture &btn_texture, int32_t tool_id);

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) {}
    virtual bool onKeyboardReleased (KeyboardKey key) {}

    virtual bool onTime (float d_seconds) {}

    virtual bool onResize(float width, float height) {return false;}
};


#endif  // TOOLBAR_HPP

