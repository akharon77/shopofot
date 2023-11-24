/**
 * @file LayoutBox.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief
 *
 * @version 0.1
 * @date 2023-11-16
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef UNIVERSAL_LAYOUT_BOX_HPP
#define UNIVERSAL_LAYOUT_BOX_HPP

#include "units.hpp"
#include "layout_box.hpp"
#include "math.hpp"

/**
 * @brief Universal layout box for almost any feasible case.
 *
 * Meaning of layout box parameters:
 *
 * <------------------------width------------------------->
 * +------------------------------------------------------+ ^
 * |                       ^                              | |
 * |                       |                              | |
 * |                       v padding_top                  | |
 * |               +--------------+                       | |
 * |               |              |                       | |
 * |  padding_left |              |   padding_right       | |
 * |<------------->|              |<--------------------->| height
 * |               |              |                       | |
 * |               +--------------+                       | |
 * |                       ^                              | |
 * |                       | padding_bottom               | |
 * |                       |                              | |
 * |                       v                              | |
 * +------------------------------------------------------+ v
 *
 *
 * Auto-alignment options:
 *
 * +------------------------parent------------------------+
 * |+----------+         +----------+         +----------+|
 * ||          |         |   Top    |         |    Top   ||
 * || Top left |         |  center  |         |   right  ||
 * ||          |         |          |         |          ||
 * |+----------+         +----------+         +----------+|
 * |                                                      |
 * |                     <---width-->                     |
 * |+----------+        ^+----------+         +----------+|
 * ||  Center  |        ||          |         |  Center  ||
 * ||   left   |  height||  Center  |         |   right  ||
 * ||          |        ||          |         |          ||
 * |+----------+        v+----------+         +----------+|
 * |                                                      |
 * |                                                      |
 * |+----------+         +----------+         +----------+|
 * ||  Bottom  |         |  Bottom  |         |  Bottom  ||
 * ||   left   |         |  center  |         |   right  ||
 * ||          |         |          |         |          ||
 * |+----------+         +----------+         +----------+|
 * +------------------------------------------------------+
 *
 * Free alignment does not constrain layout box position
 *
 */
class UniversalLayoutBox : public LayoutBox
{
    public:
        UniversalLayoutBox() : UniversalLayoutBox(100_per, 100_per)
        {}

        UniversalLayoutBox(const Length &width, const Length &height,
                Align align = Align::Free, bool resizable = true)
            : m_align(align), m_posX(0_px), m_posY(0_px), m_resizable(resizable),
            m_width(width), m_height(height), m_paddingTop(0_px),
            m_paddingBottom(0_px), m_paddingLeft(0_px), m_paddingRight(0_px),
            m_parentSize(1, 1)
        {}

        UniversalLayoutBox(const UniversalLayoutBox &other)
            : m_align(other.m_align), m_posX(other.m_posX), m_posY(other.m_posY),
            m_resizable(other.m_resizable), m_width(other.m_width),
            m_height(other.m_height), m_paddingTop(other.m_paddingTop),
            m_paddingBottom(other.m_paddingBottom),
            m_paddingLeft(other.m_paddingLeft),
            m_paddingRight(other.m_paddingRight), m_parentSize(1, 1)
        {}

        /**
         * @brief Update padding in all directions
         *
         * @param[in] padding	New padding value
         */
        void setPadding(const Length &padding)
        {
            setPadding(padding, padding, padding, padding);
        }

        /**
         * @brief Update horizontal and vertical padding
         *
         * @param[in] top_bottom  New vertical padding value
         * @param[in] left_right	New horizontal padding value
         */
        void setPadding(const Length &top_bottom, const Length &left_right)
        {
            setPadding(top_bottom, top_bottom, left_right, left_right);
        }

        /**
         * @brief Update all padding values separately
         *
         * @param[in] top	    New top padding value
         * @param[in] bottom  New bottom padding value
         * @param[in] left	  New left padding value
         * @param[in] right	  New right padding value
         *
         */
        void setPadding(const Length &top,  const Length &bottom,
                        const Length &left, const Length &right)
        {
            m_paddingTop = top;
            m_paddingBottom = bottom;
            m_paddingLeft = left;
            m_paddingRight = right;
        }

        /**
         * @brief Update layout box size
         *
         * @param[in] width	  New layout box width
         * @param[in] height	New layout box height
         */
        void setSize(const Length &width, const Length &height)
        {
            setWidth(width);
            setHeight(height);
        }

        /**
         * @brief Update layout box width
         *
         * @param[in] width	  New layout box width
         */
        void setWidth(const Length &width) 
        {
            m_width = width;
        }

        /**
         * @brief Update layout box height
         *
         * @param[in] height	New layout box height
         */
        void setHeight(const Length &height)
        {
            m_height = height;
        }

        /**
         * @brief Update layout box alignment type
         *
         * @param[in] align	  New layout box alignment type
         */
        void setAlignment(Align align)
        {
            m_align = align;
        }

        /**
         * @brief Allow resizing of this layout box.
         *
         * `plug::LayoutBox::setSize()` will function normally and return `true`
         */
        void unlockSize()
        {
            m_resizable = true;
        }

        /**
         * @brief Disable resizing of this layout box
         *
         * `plug::LayoutBox::setSize()` will not update size and will always return
         * `false`
         */
        void lockSize()
        {
            m_resizable = false;
        }

        /*****************************************************************************
         *
         * plug::LayoutBox implementation
         *
         ****************************************************************************/

        virtual void onParentUpdate(const LayoutBox &parent_box) override;

        virtual Vec2d getSize() const override;

        virtual Vec2d getPosition() const override;

        virtual bool setSize(const Vec2d &size) override;

        virtual bool setPosition(const Vec2d &position) override;

        virtual LayoutBox *clone(void) const override
        {
            return new UniversalLayoutBox(*this);
        }

    private:
        Align m_align;
        Length m_posX;
        Length m_posY;

        bool m_resizable;
        Length m_width;
        Length m_height;

        Length m_paddingTop;
        Length m_paddingBottom;
        Length m_paddingLeft;
        Length m_paddingRight;

        Vec2d m_parentSize;
};

#endif  // UNIVERSAL_LAYOUT_BOX_HPP

