#ifndef FRAME_HPP
#define FRAME_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "button.hpp"

// class CloseButton : public Button
// {
// public:
//     virtual void onClick()    {};
//     virtual void onReleased() {};
// };

class Frame : public Widget
{
    enum status_t
    {
        DEFAULT,
        HOLD
    };

    Widget *m_wrappee;

    const char *m_title;

    float m_thickness;

    float m_width;
    float m_height;

    sf::VertexArray m_vertex_array;

    status_t m_status;
    Vector2f m_hold_pos;

    //CloseButton m_close_btn;

public:
    Frame(Widget &wrappee, const char *title, float thickness, float width, float height);

    ~Frame() = default;
    Frame& operator = (const Frame &rhs) = delete;
    Frame(const Frame &rhs) = delete;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onTime (float d_seconds) override;
};

#endif  // FRAME_HPP

