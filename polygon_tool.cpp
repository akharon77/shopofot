#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "polygon_tool.hpp"
#include "canvas.hpp"

void PolygonToolWidget::draw(sf::RenderTarget &target, List<Transform> &transf_list)
{
    if (m_status == DEFAULT)
        return;

    Transform top_transf = transf_list.Get(transf_list.GetTail())->val;
    sf::VertexArray arr(m_arr);
    arr.append(static_cast<Vector2f>(m_pos));
    arr.append(arr[0]);

    for (int32_t i = 0; i < arr.getVertexCount(); ++i)
        arr[i].position = static_cast<Vector2f>(top_transf.apply(static_cast<Vec2d>(arr[i].position)));

    target.draw(arr);
}

void PolygonTool::onMainButton(MouseType key, Vector2f pos, Canvas &canvas)
{
    if (key == MouseType::PRESSED)
    {
        m_widget.m_status = PolygonToolWidget::ACTIVE;
        m_widget.m_pos = static_cast<Vec2d>(pos);
    }
    else if (m_widget.m_status == PolygonToolWidget::ACTIVE && key == MouseType::RELEASED)
    {
        m_widget.m_arr.append(pos);
        m_widget.m_pos = static_cast<Vec2d>(pos);
    }
}

void PolygonTool::onMove(Vector2f pos, Canvas &canvas)
{
    m_widget.m_pos = static_cast<Vec2d>(pos);
}

void PolygonTool::onConfirm(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = PolygonToolWidget::DEFAULT;

    sf::VertexArray arr(m_widget.m_arr);
    arr.append(arr[0]);

    for (int32_t i = 0; i < arr.getVertexCount(); ++i)
    {
        arr[i].position.x *= canvas.m_canv_width;
        arr[i].position.y *= canvas.m_canv_height;
    }

    canvas.m_canv_texture.draw(arr);

    m_widget.m_arr.resize(0);
}

void PolygonTool::onCancel(Vector2f pos, Canvas &canvas)
{
    m_widget.m_status = PolygonToolWidget::DEFAULT;
    m_widget.m_arr.clear();
}

