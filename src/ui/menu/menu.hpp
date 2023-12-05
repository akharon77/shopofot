#ifndef MENU_HPP
#define MENU_HPP

#include "list.hpp"
#include "widget.hpp"
#include "button.hpp"
#include "universal_layout_box.hpp"

class Menu : public Widget
{
    Widget *m_wrappee;
    LayoutBox *m_wrappee_stolen_layout_box;
    List<Button*> m_btn_list;

    double m_right_corner;
    double m_max_height;

public:
    Menu(Widget &wrappee);

    ~Menu() = default;
    Menu& operator = (const Menu &rhs) = delete;
    Menu(const Menu &rhs) = delete;

    void addButton(Button &btn);

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onTime (float d_seconds) override;

    virtual bool onResize(float width, float height) override;
};

#endif

