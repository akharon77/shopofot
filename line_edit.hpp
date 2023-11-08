#ifndef LINE_EDIT_HPP
#define LINE_EDIT_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "widget.hpp"

class LineEdit : public Widget
{
    char m_buf[256];
    int32_t m_len;

    bool m_shift_flag;

    char m_last_char;

    enum class status_t
    {
        DEFAULT,
        PRESSED
    };

    status_t m_status;
    bool m_cursor_flag;
    float m_accum;

public:
    sf::Text m_text;
    float m_thickness;

    LineEdit(Vector2f pos, float width, float height, sf::Font &font, float thickness);

    ~LineEdit() = default;
    LineEdit& operator = (const LineEdit &rhs) = delete;
    LineEdit(const LineEdit &rhs) = delete;

    void clear();

    void draw(sf::RenderTarget &target, Vector2f pos);

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onTime (float d_seconds) override;

    virtual bool onResize(float width, float height) override;
};

#endif  // LINE_EDIT_HPP

