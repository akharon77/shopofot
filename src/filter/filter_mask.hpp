#ifndef FILTER_FILTER_MASK_HPP
#define FILTER_FILTER_MASK_HPP

#include <cstdint>

class FilterMask
{
    uint32_t m_width;
    uint32_t m_height;

    bool *m_buf;

public:
    FilterMask(size_t width, size_t height);
    ~FilterMask();

    FilterMask(const FilterMask &rhs)             = delete;
    FilterMask operator = (const FilterMask &rhs) = delete;

    void resize(size_t width, size_t height);

    size_t getWidth()  const;
    size_t getHeight() const;

    bool getPixel(size_t x, size_t y) const;
    void setPixel(size_t x, size_t y, bool value);

    void fill(bool value);

    void invert();
};

#endif  // FILTER_FILTER_MASK_HPP

