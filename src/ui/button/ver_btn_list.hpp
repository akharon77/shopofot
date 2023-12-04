#ifndef VER_BTN_LIST_HPP
#define VER_BTN_LIST_HPP

#include "list.hpp"
#include "widget.hpp"
#include "text_btn.hpp"
#include "layout_box.hpp"

class VerticalButtonList : public TextButton
{
    enum status_t
    {
        DEFAULT,
        OPENED
    };

    status_t m_status;

    List<Button*> m_btn_lst;

    double m_bottom;

public:
    VerticalButtonList(const LayoutBox &box, const char *str, TextButtonTexture &m_btn_texture);

    ~VerticalButtonList() = default;
    VerticalButtonList& operator = (const VerticalButtonList &rhs) = delete;
    VerticalButtonList(const VerticalButtonList &rhs) = delete;

    int32_t addButton(Button &btn);
    Button *popButton();

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onTime (float d_seconds) override;

    // virtual bool onResize(float width, float height) override;
};

#endif  // VER_BTN_LIST_HPP

