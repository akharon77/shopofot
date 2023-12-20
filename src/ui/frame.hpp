#ifndef UI_FRAME_HPP
#define UI_FRAME_HPP

#include "ui/button.hpp"
#include "widget.hpp"
#include "universal_layoutbox.hpp"

#include <SFML/Graphics.hpp>

struct FrameTexture
{
    ButtonTexture *m_close_btn_texture;
    ButtonTexture *m_full_btn_texture;
    sf::Font &font;
};

class Frame : public Widget
{
    class CloseButton : public Button
    {
        Container *m_container;
        int32_t    m_close_id;

    public:
        CloseButton(const ButtonTexture &btn_texture) :
            Button(UniversalLayoutBox(), btn_texture)
        {};

        ~CloseButton() = default;
        CloseButton(const CloseButton &rhs) = delete;
        CloseButton& operator = (const CloseButton& rhs) = delete;

        void setContainer(Container &container);
        void setCloseId(int32_t id);

        virtual void onMousePressed(plug::MouseButton key, double x, double y, plug::EHC &context) override;
    };

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

    plug::Widget *m_wrappee;

    const char *m_title;

    double m_thickness;

    plug::LayoutBox *m_wrappee_stolen_layout_box;

    plug::VertexArray m_vertex_array;

    status_t m_status;
    plug::Vec2d    m_hold_pos;

    FrameTexture *m_frame_texture;

    plug::Texture *m_texture;
    Rect  m_rect;

    interactive_t m_interactive;

    CloseButton m_close_btn;

    void updateVertexArray();

public:
    Frame(Widget &wrappee, const char *title, double thickness, FrameTexture &frame_texture);

    ~Frame() = default;
    Frame& operator = (const Frame &rhs) = delete;
    Frame(const Frame &rhs) = delete;

    void setClosable(bool flag);
    void setCloseId(int32_t id);
    void setContainer(Container &container);

    virtual void draw(plug::TransformStack &stack, plug::RenderTarget &target) override;

    virtual void onTime(double d_seconds, plug::EHC &context) override;

    virtual void onMouseMoved (double x, double y, plug::EHC &context) override;

    virtual void onMousePressed  (plug::MouseButton key, double x, double y, plug::EHC &context) override;
    virtual void onMouseReleased (plug::MouseButton key, double x, double y, plug::EHC &context) override;

    virtual void onKeyboardPressed  (plug::KeyCode key, plug::EHC &context) override;
    virtual void onKeyboardReleased (plug::KeyCode key, plug::EHC &context) override;

    virtual void onResize(double width, double height, plug::EHC &context) override;
};

#endif  // UI_FRAME_HPP

