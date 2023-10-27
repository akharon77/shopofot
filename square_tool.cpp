#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "square_tool.hpp"
#include "canvas.hpp"

void SquareToolWidget::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    if (m_status == DEFAULT)
        return;

    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
    
    sf::VertexArray arr(sf::Quads, 4);
    arr[0].position = m_hold_pos;
    arr[1].position = Vector2f{m_pos.x, m_hold_pos.y};
    arr[2].position = Vector2f{m_pos.x, m_pos.y};
    arr[3].position = Vector2f{m_hold_pos.x, m_pos.y};
    for (int32_t i = 0; i < 4; ++i)
        arr[i].position = top_transf.rollbackTransform(arr[i].position);

    target.draw(arr);
}

void SquareTool::onMainButton(MouseType key, Vector2f pos, Canvas &canvas)
{
    if (key == MouseType::PRESSED)
    {
        m_status = HOLD;
        m_widget.m_status = SquareToolWidget::HOLD;
        m_widget.m_hold_pos = m_widget.m_pos = pos;
    }
    else if (key == MouseType::RELEASED && m_status == HOLD)
    {
        m_status = DEFAULT;
        m_widget.m_status = SquareToolWidget::DEFAULT;

        sf::VertexArray arr(sf::Quads, 4);
        arr[0].position = m_widget.m_hold_pos;
        arr[1].position = Vector2f{pos.x, m_widget.m_hold_pos.y};
        arr[2].position = Vector2f{pos.x, pos.y};
        arr[3].position = Vector2f{m_widget.m_hold_pos.x, pos.y};
        for (int32_t i = 0; i < 4; ++i)
        {
            arr[i].position.x *= canvas.m_canv_width;
            arr[i].position.y *= canvas.m_canv_height;
        }

        canvas.m_canv_texture.draw(arr);
    }
}

void SquareTool::onMove(Vector2f pos, Canvas &canvas)
{
    if (m_widget.m_status == SquareToolWidget::HOLD)
        m_widget.m_pos = pos;
}

void SquareTool::onCancel(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = SquareToolWidget::DEFAULT;
}

void SquareTool::onConfirm(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = SquareToolWidget::DEFAULT;
}

