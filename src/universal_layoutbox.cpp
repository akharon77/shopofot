#include "universal_layoutbox.hpp"
#include "units.hpp"
#include "math.hpp"

static double getPixels(const Length &len, double parent_len)
{
    if (len.unit == Unit::Percent)
        return parent_len * len.value / 100;

    return (double) len;
}

static Length fromPixels(double pixels, Unit unit, double parent_pixels)
{
    double value = 0;
    switch (unit)
    {
        case Unit::Pixel:
            value = pixels;
            break;

        case Unit::Centimeter:
            value = pixels / PixelsPerInch * CentimetersPerInch;
            break;

        case Unit::Millimeter:
            value = pixels / PixelsPerInch * CentimetersPerInch * MillimitersPerCentimeter;
            break;

        case Unit::Inch:
            value = pixels / PixelsPerInch;
            break;

        case Unit::Percent:
            value = pixels / parent_pixels * 100;
            break;

        default:
            value = 0;
            break;
    }

    return Length(value, unit);
}

static double clampToZero(double val)
{
    if (val < 0)
        return 0;

    return val;
}

void UniversalLayoutBox::onParentUpdate(const Vec2d &parent_size)
{
    m_parentSize = parent_size;

    if (m_align == Align::Free)
    {
        return;
    }

    Vec2d full_size(getPixels(m_width,  m_parentSize.x),
                    getPixels(m_height, m_parentSize.y));

    const double pad_left = getPixels(m_paddingLeft, m_parentSize.x);
    const double pad_top  = getPixels(m_paddingTop,  m_parentSize.y);

    const double unit_x = fabs(m_parentSize.x - full_size.x) / 2;
    const double unit_y = fabs(m_parentSize.y - full_size.y) / 2;

    double start_x = m_parentSize.x < full_size.x ? -2 * unit_x : 0;
    double start_y = m_parentSize.y < full_size.y ? -2 * unit_y : 0;

    Vec2d pos(start_x, start_y);

    switch (m_align)
    {
        case Align::TopLeft:      pos += Vec2d(         0,          0); break;
        case Align::TopCenter:    pos += Vec2d(    unit_x,          0); break;
        case Align::TopRight:     pos += Vec2d(2 * unit_x,          0); break;
        case Align::CenterLeft:   pos += Vec2d(         0,     unit_y); break;
        case Align::Center:       pos += Vec2d(    unit_x,     unit_y); break;
        case Align::CenterRight:  pos += Vec2d(2 * unit_x,     unit_y); break;
        case Align::BottomLeft:   pos += Vec2d(         0, 2 * unit_y); break;
        case Align::BottomCenter: pos += Vec2d(    unit_x, 2 * unit_y); break;
        case Align::BottomRight:  pos += Vec2d(2 * unit_x, 2 * unit_y); break;
        case Align::Free:
        default:
              break;
    }

    m_posX = fromPixels(pos.x + pad_left, m_posX.unit, m_parentSize.x);
    m_posY = fromPixels(pos.y + pad_top,  m_posY.unit, m_parentSize.y);
}

void UniversalLayoutBox::onParentUpdate(const LayoutBox &parent_box)
{
    onParentUpdate(parent_box.getSize());
}

bool UniversalLayoutBox::setSize(const Vec2d &size)
{
    if (!m_resizable)
    {
        return false;
    }

    m_width  = fromPixels(size.x, m_width.unit,  m_parentSize.x);
    m_height = fromPixels(size.y, m_height.unit, m_parentSize.y);

    return true;
}

bool UniversalLayoutBox::setPosition(const Vec2d &position)
{
    if (m_align != Align::Free)
        return false;

    m_posX = fromPixels(position.x, m_posX.unit, m_parentSize.x);
    m_posY = fromPixels(position.y, m_posY.unit, m_parentSize.y);

    return true;
}

Vec2d UniversalLayoutBox::getSize() const
{
    const double full_width  = getPixels(m_width,  m_parentSize.x);
    const double full_height = getPixels(m_height, m_parentSize.y);

    const double pad_horiz = getPixels(m_paddingLeft,  m_parentSize.x) +
                             getPixels(m_paddingRight, m_parentSize.x);

    const double pad_vert = getPixels(m_paddingTop,    m_parentSize.y) +
                            getPixels(m_paddingBottom, m_parentSize.y);

    return Vec2d(clampToZero(full_width  - pad_horiz),
                 clampToZero(full_height - pad_vert));
}

Vec2d UniversalLayoutBox::getPosition() const
{
    return Vec2d(getPixels(m_posX, m_parentSize.x),
                 getPixels(m_posY, m_parentSize.y));
}

