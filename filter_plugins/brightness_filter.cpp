#include "brightness_filter.hpp"
#include "canvas.hpp"

BrightnessFilter::BrightnessFilter() :
    m_ref_cnt(0),
    m_delta(0.1)
{}

Plugin *BrightnessFilter::tryGetInterface(size_t interface_id)
{
    Plugin *result = nullptr;

    switch ((PluginGuid) interface_id)
    {
        case PluginGuid::Plugin:
            result = (Plugin*) this;
            break;
        case PluginGuid::Filter:
            result = (Filter*) this;
            break;
        default:
            result = nullptr;
    }

    if (result)
        result->addReference();

    return result;
}

void BrightnessFilter::addReference()
{
    ++m_ref_cnt;
}

void BrightnessFilter::release()
{
    --m_ref_cnt;

    if (m_ref_cnt == 0)
        delete this;
}

void BrightnessFilter::setBrightnessDelta(float delta)
{
    m_delta = delta;
    m_plugin_data.m_sign = delta > EPS;
}

void BrightnessFilter::applyFilter(Canvas &canvas, const FilterMask &mask)
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
            float r_dash = color.r / 255.f;
            float g_dash = color.g / 255.f;
            float b_dash = color.b / 255.f;

            float c_max = std::max(std::max(r_dash, g_dash), b_dash);
            float c_min = std::min(std::min(r_dash, g_dash), b_dash);

            float delta = c_max - c_min;
            
            float hue = -1;
            if (fabs(delta) < EPS)
                hue = 0;
            else if (fabs(c_max - r_dash) < EPS)
                hue = 60 * ((g_dash - b_dash) / delta + 0);
            else if (fabs(c_max - g_dash) < EPS)
                hue = 60 * ((b_dash - r_dash) / delta + 2);
            else if (fabs(c_max - b_dash) < EPS)
                hue = 60 * ((r_dash - g_dash) / delta + 4);

            float lightness = (c_min + c_max) / 2;

            float saturation = -1;
            if (fabs(delta) < EPS)
                saturation = 0;
            else
                saturation = delta / (1 - fabs(2 * lightness - 1));

            lightness += m_delta;

            float c = (1 - fabs(2 * lightness - 1)) * saturation;
            float x = c * (1 - fabs(fmod(hue / 60, 2) - 1));
            float m = lightness - c / 2;
            
            if (hue < 60 + EPS)
            {
                r_dash = c;
                g_dash = x;
                b_dash = 0;
            }
            else if (hue < 120 + EPS)
            {
                r_dash = x;
                g_dash = c;
                b_dash = 0;
            }
            else if (hue < 180 + EPS)
            {
                r_dash = 0;
                g_dash = c;
                b_dash = x;
            }
            else if (hue < 240 + EPS)
            {
                r_dash = 0;
                g_dash = x;
                b_dash = c;
            }
            else if (hue < 300 + EPS)
            {
                r_dash = x;
                g_dash = 0;
                b_dash = c;
            }
            else if (hue < 360 + EPS)
            {
                r_dash = c;
                g_dash = 0;
                b_dash = x;
            }

            color.r = std::max(0, std::min(255, int32_t((r_dash + m) * 255)));
            color.g = std::max(0, std::min(255, int32_t((g_dash + m) * 255)));
            color.b = std::max(0, std::min(255, int32_t((b_dash + m) * 255)));

            buf_img.setPixel(x_coord, y_coord, color);
        }
    }

    canvas.drawImage(buf_img);
}

extern "C" Plugin *loadPlugin()
{
    return new BrightnessFilter;
}
