#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "polyline_tool.hpp"
#include "canvas.hpp"

void PolyLineToolWidget::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    if (m_status == DEFAULT)
        return;

    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
    sf::VertexArray arr(m_arr);
    arr.append(sf::Vertex(static_cast<Vector2f>(m_pos)));

    for (int32_t i = 0; i < arr.getVertexCount(); ++i)
        arr[i].position = static_cast<Vector2f>(top_transf.apply(static_cast<Vec2d>(arr[i].position)));

    target.draw(arr);
}

void PolyLineTool::onMainButton(MouseType key, Vector2f pos, Canvas &canvas)
{
    if (key == MouseType::PRESSED)
    {
        if (m_widget.m_status == PolyLineToolWidget::ACTIVE)
        {
            if (m_widget.m_arr.getVertexCount() > 0 && static_cast<Vec2d>(pos - m_widget.m_arr[0].position).length() < 2 * EPS)
            {
                m_widget.m_arr.append(pos);
                onConfirm(pos, canvas);
            }
        }
        else
        {
            m_widget.m_status = PolyLineToolWidget::ACTIVE;
        }

        m_widget.m_pos = static_cast<Vec2d>(pos);
    }
    else if (m_widget.m_status == PolyLineToolWidget::ACTIVE)
    {
        m_widget.m_arr.append(pos);
        m_widget.m_pos = static_cast<Vec2d>(pos);
    }
}

void PolyLineTool::onMove(Vector2f pos, Canvas &canvas)
{
    m_widget.m_pos = static_cast<Vec2d>(pos);
}

void PolyLineTool::onConfirm(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = PolyLineToolWidget::DEFAULT;

    sf::VertexArray arr(m_widget.m_arr);

    for (int32_t i = 0; i < arr.getVertexCount(); ++i)
    {
        arr[i].position.x *= canvas.m_canv_width;
        arr[i].position.y *= canvas.m_canv_height;
    }

    canvas.m_canv_texture.draw(arr);

    m_widget.m_arr.clear();
}

void PolyLineTool::onCancel(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = PolyLineToolWidget::DEFAULT;
    m_widget.m_arr.clear();
}

