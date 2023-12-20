#ifndef UI_BUTTON_VERTICAL_BUTTON_LIST_HPP
#define UI_BUTTON_VERTICAL_BUTTON_LIST_HPP

#include "ui/button/text_button.hpp"
#include "util/list.hpp"

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
    int32_t m_thickness;

    VerticalButtonList(const plug::LayoutBox &box, const char *str, int32_t thickness, TextButtonTexture &m_btn_texture);

    ~VerticalButtonList() = default;
    VerticalButtonList& operator = (const VerticalButtonList &rhs) = delete;
    VerticalButtonList(const VerticalButtonList &rhs) = delete;

    int32_t addButton(Button &btn);
    Button *popButton();

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
    virtual void onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) override;

    virtual void onMouseMoved (double x, double y, plug::EHC &context) override;

    virtual void onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) override;
    virtual void onKeyboardReleased (plug::KeyCode key, plug::EHC &context) override;

    virtual void onTime(double d_seconds, plug::EHC &context) override;
};

#endif  // UI_BUTTON_VERTICAL_BUTTON_LIST_HPP

