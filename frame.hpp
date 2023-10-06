#ifndef FRAME_HPP
#define FRAME_HPP

class Frame : public Widget
{
    Widget *m_wrappee;

    const char *m_title;

    float m_thickness;

    float m_width;
    float m_height;

    Transform m_transf;
    
    sf::VertexArray m_vertex_array;

    CloseButton m_close_btn;

public:
    Frame(Widget *wrappee, const char *title, float thickness, Vector2f pos, float width, float height);

    ~Frame() = default;
    Frame& operator = (const Window &rhs) = delete;
    Frame(const Window &rhs) = delete;

    virtual void draw(sf::RenderTarget &target, List<Transform> &transf_list) override;

    virtual bool onMousePressed  (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;
    virtual bool onMouseReleased (MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onMouseMoved (int32_t x, int32_t y, List<Transform> &transf_list) override;

    virtual bool onKeyboardPressed  (KeyboardKey key) override;
    virtual bool onKeyboardReleased (KeyboardKey key) override;

    virtual bool onTime (float d_seconds) override;
};

class CloseButton : public Button
{
public:
    virtual void onClick()    override;
    virtual void onReleased() override;
};

#endif  // FRAME_HPP

