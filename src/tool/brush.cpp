#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "brush.hpp"
#include "canvas.hpp"

void BrushToolWidget::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    // TODO: make more based and less cringe
    // for compatibility only
    Transform m_transf(getLayoutBox().getPosition(), Vec2d(1, 1));

    transf_list.PushBack(m_transf.combine(transf_list.Get(transf_list.GetTail())->val));
    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
    
    m_shape.setPosition(static_cast<Vector2f>(top_transf.apply(Vec2d(0, 0))));
    target.draw(m_shape);

    transf_list.PopBack();
}

void BrushTool::onMainButton(MouseType key, Vector2f pos, Canvas &canvas)
{
    if (key == MouseType::PRESSED)
    {
        m_status = HOLD;
        m_prev_pos = static_cast<Vec2d>(pos);
    }
    else
    {
        m_status = DEFAULT;
    }
}

void BrushTool::onMove(Vector2f pos, Canvas &canvas)
{
    if (m_status == HOLD)
    {
        sf::CircleShape shape(1);
        shape.setOrigin(0.5, 0.5);

        Vector2f delta = pos - static_cast<Vector2f>(m_prev_pos);
        delta.x /= 10;
        delta.y /= 10;
        for (int32_t i = 0; i < 10; ++i)
        {
            m_prev_pos += static_cast<Vec2d>(delta);
            shape.setPosition({m_prev_pos.x * canvas.m_canv_width, m_prev_pos.y * canvas.m_canv_height});

            canvas.m_canv_texture.draw(shape);
            canvas.m_canv_texture.display();
        }
    }

    m_widget.getLayoutBox().setPosition(static_cast<Vec2d>(pos));
    // m_widget.m_transf.m_offset = pos;
}

