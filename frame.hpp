#ifndef FRAME_HPP
#define FRAME_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

// #include "button.hpp"
#include "units.hpp"
#include "widget.hpp"

struct FrameTexture
{
    // ButtonTexture *m_close_btn_texture;
    // ButtonTexture *m_full_btn_texture;
};

class Frame : public Widget
{
    // class CloseButton : public Button
    // {
    //     Container *m_container;
    //     int32_t    m_close_id;

    // public:
    //     CloseButton(const ButtonTexture &btn_texture) :
    //         Button({0, 0}, 0, 0, btn_texture)
    //     {};

    //     ~CloseButton() = default;
    //     CloseButton(const CloseButton &rhs) = delete;
    //     CloseButton& operator = (const CloseButton& rhs) = delete;

    //     void setContainer(Container &container);
    //     void setCloseId(int32_t id);

    //     virtual bool onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    // };

    enum class status_t : uint8_t
    {
        DEFAULT  = 0,
        HOLD     = 1,
        HOLD_VER = 1 << 1,
        HOLD_HOR = 1 << 2
    };

    enum class interactive_t : uint8_t
    {
        DEFAULT  = 0,
        CLOSABLE = 1,
        FULLABLE = 1 << 1
    };

    Widget *m_wrappee;

    const char *m_title;

    Length m_thickness;

    double m_width;
    double m_height;

    LayoutBox *m_wrappee_stolen_layout_box;

    sf::VertexArray m_vertex_array;

    status_t m_status;
    Vec2d    m_hold_pos;

    FrameTexture *m_frame_texture;

    sf::Texture *m_texture;
    sf::IntRect  m_rect;

    interactive_t m_interactive;

    // CloseButton m_close_btn;

    void updateVertexArray();

public:
    Frame(Widget &wrappee, const char *title, const Length &thickness, FrameTexture &frame_texture);

    ~Frame() = default;
    Frame& operator = (const Frame &rhs) = delete;
    Frame(const Frame &rhs) = delete;

    // void setClosable(bool flag);
    // void setCloseId(int32_t id);
    // void setContainer(Container &container);

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onResize(float width, float height) override;

    virtual bool onTime (float d_seconds) override;
};

#endif  // FRAME_HPP

