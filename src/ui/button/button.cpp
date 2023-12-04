 #include "button.hpp"

// ButtonTexture::ButtonTexture(const sf::Texture &texture, const sf::IntRect &default_rect, const sf::IntRect &pressed_rect, const sf::IntRect &focused_rect) :
//     m_texture(&texture),
//     m_default_rect(default_rect),
//     m_pressed_rect(pressed_rect),
//     m_focused_rect(focused_rect)
// {}

Button::Button(const LayoutBox &box, const ButtonTexture &btn_texture) :
    Widget(box),
    m_status(DEFAULT),
    // m_width(box.getSize().x),
    // m_height(box.getSize().y),
    m_btn_texture(btn_texture),
    m_vertex_array(sf::Quads, 4)
{
    m_vertex_array[0].position = {0, 0};
    m_vertex_array[1].position = {1, 0};
    m_vertex_array[2].position = {1, 1};
    m_vertex_array[3].position = {0, 1};

    setRect(m_btn_texture.m_default_rect);
}

void Button::setRect(const sf::IntRect &rect)
{
    m_vertex_array[0].texCoords = {rect.left,              rect.top};
    m_vertex_array[1].texCoords = {rect.left + rect.width, rect.top};
    m_vertex_array[2].texCoords = {rect.left + rect.width, rect.top + rect.height};
    m_vertex_array[3].texCoords = {rect.left,              rect.top + rect.height};
}
 
void Button::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    sf::VertexArray buf_vertex_array(m_vertex_array);
    for (int32_t i = 0; i < 4; ++i)
        buf_vertex_array[i].position = static_cast<Vector2f>(top_transf.apply(static_cast<Vec2d>(m_vertex_array[i].position)));

    target.draw(buf_vertex_array, m_btn_texture.m_texture);

    transf_list.PopBack();
}

bool Button::onMousePressed(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        m_status = PRESSED;
        setRect(m_btn_texture.m_pressed_rect);

        transf_list.PopBack();
        return true;
    }

    transf_list.PopBack();
    return false;
}

bool Button::onMouseReleased(MouseKey key, int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (m_status == PRESSED)
    {
        if (EPS < pos.x && pos.x < 1 - EPS &&
            EPS < pos.y && pos.y < 1 - EPS)
        {
            m_status = FOCUSED;
            setRect(m_btn_texture.m_focused_rect);

            transf_list.PopBack();
            return true;
        }
        else
        {
            m_status = DEFAULT;
            setRect(m_btn_texture.m_default_rect);
        }
    }

    transf_list.PopBack();
    return false;
}

bool Button::onMouseMoved(int32_t x, int32_t y, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), getLayoutBox().getSize());

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;

    bool res = false;

    Vec2d pos = top_transf.restore(Vec2d(x, y));

    if (m_status == DEFAULT            &&
        EPS < pos.x && pos.x < 1 - EPS &&
        EPS < pos.y && pos.y < 1 - EPS)
    {
        m_status = FOCUSED;
        res = true;
        setRect(m_btn_texture.m_focused_rect);
    }
    else if (m_status != DEFAULT              &&
             !(EPS < pos.x && pos.x < 1 - EPS &&
               EPS < pos.y && pos.y < 1 - EPS))
    {
        m_status = DEFAULT;
        res = true;
        setRect(m_btn_texture.m_default_rect);
    }

    transf_list.PopBack();
    return res;
}

bool Button::onResize(float width, float height)
{
    // m_size = {width, height};
    getLayoutBox().setSize(Vec2d(width, height));
    // m_transf.m_scale = m_size;
    // m_width = width;
    // m_height = height;
}
