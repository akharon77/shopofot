#ifndef UI_MENU_HPP
#define UI_MENU_HPP

#include "util/list.hpp"
#include "widget.hpp"
#include "ui/button/button.hpp"

class Menu : public Widget
{
    plug::Widget *m_wrappee;
    plug::LayoutBox *m_wrappee_stolen_layout_box;
    List<Button*> m_btn_list;

    double m_right_corner;
    double m_max_height;

public:
    Menu(plug::Widget &wrappee);

    ~Menu() = default;
    Menu& operator = (const Menu &rhs) = delete;
    Menu(const Menu &rhs) = delete;

    void addButton(Button &btn);

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual void onTime(double d_seconds, plug::EHC &context) override;

    virtual void onMouseMoved (double x, double y, plug::EHC &context) override;

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
    virtual void onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) override;

    virtual void onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) override;
    virtual void onKeyboardReleased (plug::KeyCode key, plug::EHC &context) override;

    virtual void onResize(double width, double height, plug::EHC &context) override;
};

#endif  // UI_MENU_HPP

