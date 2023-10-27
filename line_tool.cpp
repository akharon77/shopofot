#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "line_tool.hpp"
#include "canvas.hpp"

void LineToolWidget::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    if (m_status == DEFAULT)
        return;

    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
    sf::Vertex line[] =
    {
        sf::Vertex{top_transf.rollbackTransform(m_first_pos)},
        sf::Vertex{top_transf.rollbackTransform(m_second_pos)}
    };

    target.draw(line, 2, sf::Lines);
}

void LineTool::onMainButton(MouseType key, Vector2f pos, Canvas &canvas)
{
    if (key == MouseType::PRESSED)
    {
        m_widget.m_status = LineToolWidget::HOLD;
        m_widget.m_first_pos = m_widget.m_second_pos = pos;
    }
    else if (m_widget.m_status == LineToolWidget::HOLD && key == MouseType::RELEASED)
    {
        onConfirm(pos, canvas);
    }
}

void LineTool::onMove(Vector2f pos, Canvas &canvas)
{
    if (m_widget.m_status == LineToolWidget::HOLD)
    {
        m_widget.m_second_pos = pos;
    }
}

void LineTool::onConfirm(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = LineToolWidget::DEFAULT;
    m_widget.m_second_pos = pos;

    sf::Vertex line[] =
    {
        sf::Vertex{m_widget.m_first_pos},
        sf::Vertex{m_widget.m_second_pos}
    };

    for (int32_t i = 0; i < 2; ++i)
    {
        line[i].position.x *= canvas.m_canv_width;
        line[i].position.y *= canvas.m_canv_height;
    }

    canvas.m_canv_texture.draw(line, 2, sf::Lines);
}

void LineTool::onCancel(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = LineToolWidget::DEFAULT;
}

