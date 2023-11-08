#include "blackwhite_filter.hpp"
#include "canvas.hpp"

void BlackWhiteFilter::applyFilter(Canvas &canvas, const FilterMask &mask)
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
            int32_t average = (color.r + color.g + color.b) / 3;

            color.r = color.g = color.b = average;

            buf_img.setPixel(x_coord, y_coord, color);
        }
    }

    canvas.drawImage(buf_img);
}

