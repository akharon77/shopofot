#ifndef CANVAS_SELECTION_MASK_HPP
#define CANVAS_SELECTION_MASK_HPP

#include "plug/canvas/selection_mask.hpp"

class SelectionMask : public plug::SelectionMask
{
public:
    SelectionMask(const size_t width, const size_t height);
    SelectionMask(const size_t width, const size_t height, const plug::SelectionMask &init_mask);

    virtual ~SelectionMask()
    {
        delete[] m_data;
    }

    virtual size_t getWidth(void)  const { return m_width; }
    virtual size_t getHeight(void) const { return m_height; }

    virtual bool getPixel(size_t x, size_t y) const;
    virtual void setPixel(size_t x, size_t y, bool value);

    virtual void fill(bool value);
    virtual void invert(void);

private:
    size_t m_width;
    size_t m_height;
    bool *m_data;
};

#endif
