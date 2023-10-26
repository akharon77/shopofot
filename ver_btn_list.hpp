#ifndef VER_BTN_LIST_HPP
#define VER_BTN_LIST_HPP

#include "list.hpp"
#include "widget.hpp"
#include "button.hpp"

class VerticalButtonList : public Widget
{
    List<Button*> m_btn_list;

public:
    VerticalButtonList(Vector2f pos);

    ~VerticalButtonList() = default;
    VerticalButtonList& operator = (const VerticalButtonList &rhs) = delete;
    VerticalButtonList(const VerticalButtonList &rhs) = delete;

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

#endif  // VER_BTN_LIST_HPP

