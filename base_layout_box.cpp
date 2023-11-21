#include "base_layout_box.hpp"

const Vec2d BaseLayoutBox::INVALID_PAR_SIZE = Vec2d(-1, -1);

BaseLayoutBox::BaseLayoutBox(const Vec2d &pos, const Vec2d &size) :
    m_pos(pos),
    m_size(size),
    m_resizable(false),
    m_local(false),
    m_old_parent_size(INVALID_PAR_SIZE)
{}

Vec2d BaseLayoutBox::getSize() const
{
    return m_size;
}

Vec2d BaseLayoutBox::getPosition() const
{
    return m_pos;
}

bool BaseLayoutBox::setSize(const Vec2d &size)
{
    m_size = size;
    return true;
}

bool BaseLayoutBox::setPosition(const Vec2d &pos)
{
    m_pos = pos;
    return true;
}

LayoutBox *BaseLayoutBox::clone() const
{
    return new BaseLayoutBox(*this);
}

void BaseLayoutBox::setResizable(bool flag)
{
    m_resizable = flag;
}

void BaseLayoutBox::setLocal(bool flag)
{
    m_local = flag;
}

void BaseLayoutBox::onParentUpdate(const LayoutBox &parent_box)
{
    if (m_old_parent_size != INVALID_PAR_SIZE)
    { 
        if (m_resizable)
        {
            Vec2d delta_size = parent_box.getSize() - m_old_parent_size;
            m_size += delta_size;
        }

        if (m_local)
        {
            Vec2d local_pos = m_pos / m_old_parent_size;
            m_pos = local_pos * parent_box.getSize();
        }
    }

    m_old_parent_size = parent_box.getSize();
}

