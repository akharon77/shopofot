#ifndef BASE_LAYOUT_BOX_HPP
#define BASE_LAYOUT_BOX_HPP

#include "layout_box.hpp"

class BaseLayoutBox : public LayoutBox
{
    static const Vec2d INVALID_PAR_SIZE;
    Vec2d m_pos;
    Vec2d m_size;

    bool m_resizable;
    bool m_local;

    Vec2d m_old_parent_size;

public:
    BaseLayoutBox(const Vec2d &pos, const Vec2d &size);

    ~BaseLayoutBox()                                     = default;
    BaseLayoutBox(const BaseLayoutBox &rhs)              = default;
    BaseLayoutBox &operator = (const BaseLayoutBox &rhs) = default;

    virtual void onParentUpdate (const LayoutBox &parent_box) override;

    virtual Vec2d getSize     (void) const override;
    virtual Vec2d getPosition (void) const override;

    virtual bool setSize     (const Vec2d &size) override;
    virtual bool setPosition (const Vec2d &pos)  override;

    virtual LayoutBox* clone (void) const override;

    void setResizable (bool flag);
    void setLocal     (bool flag);
};

#endif  // BASE_LAYOUT_BOX_HPP

