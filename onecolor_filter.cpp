#include "onecolor_filter.hpp"
#include "canvas.hpp"

OneColorFilter::OneColorFilter(uint8_t mask) :
    m_mask((mask_t) mask)
{}

void OneColorFilter::applyFilter(Canvas &canvas, const FilterMask &mask)
{
    sf::Image buf_img = canvas.getImage();
    sf::Vector2u size = buf_img.getSize();

    for (int32_t x_coord = 0; x_coord < size.x; ++x_coord)
    {
        for (int32_t y_coord = 0; y_coord < size.y; ++y_coord)
        {
            if (!mask.getPixel(x_coord, y_coord))
            {
                buf_img.setPixel(x_coord, y_coord, sf::Color::Transparent);
                continue;
            }

            sf::Color color = buf_img.getPixel(x_coord, y_coord);
            if (!(m_mask & RED))
                color.r = 0;
            if (!(m_mask & GREEN))
                color.g = 0;
            if (!(m_mask & BLUE))
                color.b = 0;

            buf_img.setPixel(x_coord, y_coord, color);
        }
    }

    canvas.drawImage(buf_img);
}

