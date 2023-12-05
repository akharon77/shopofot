#ifndef PLUG_GRAPHICS_VERTEX_ARRAY_HPP
#define PLUG_GRAPHICS_VERTEX_ARRAY_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>

#include "plug/color.hpp"
#include "plug/graphics/primitive_type.hpp"
#include "plug/math.hpp"

namespace plug
{
    struct Vertex
    {
        Vec2d position;
        Vec2d tex_coords;
        Color color;
    };

    class VertexArray
    {
        public:
            VertexArray(PrimitiveType type, size_t size);
            VertexArray(const VertexArray &other);
            VertexArray &operator = (const VertexArray &other);

            ~VertexArray(void);

            PrimitiveType getPrimitive (void) const;
            void          setPrimitive (PrimitiveType type);

            size_t getSize (void) const;
            void   resize  (size_t new_size);

            void appendVertex(const Vertex &vertex);

            Vertex       &operator[](size_t index);
            const Vertex &operator[](size_t index) const;

        private:
            PrimitiveType m_type;

            Vertex *m_data;
            size_t  m_size;
            size_t  m_capacity;

            void reserve(size_t new_capacity);
    };

    inline VertexArray::VertexArray(PrimitiveType type, size_t size = 0) :
        m_type(type),
        m_size(size),
        m_capacity(std::max(size, 1ul))
    {
        m_data = new Vertex[m_capacity];
    }

    inline VertexArray::VertexArray(const VertexArray &other) :
        m_type(other.m_type),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        m_data = new Vertex[m_capacity];
        for (size_t ind = 0; ind < m_size; ++ind)
            m_data[ind] = other.m_data[ind];
    }

    inline VertexArray &VertexArray::operator = (const VertexArray &other)
    {
        if (this == &other)
            return *this;

        delete[] m_data;

        m_type = other.m_type;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        m_data = new Vertex[m_capacity];
        for (size_t ind = 0; ind < m_size; ++ind)
            m_data[ind] = other.m_data[ind];

        return *this;
    }

    inline VertexArray::~VertexArray(void)
    {
        m_size = m_capacity = -1;
        delete[] m_data;
    }

    inline PrimitiveType VertexArray::getPrimitive(void) const
    {
        return m_type;
    }

    inline void VertexArray::setPrimitive(PrimitiveType type)
    {
        m_type = type;
    }

    inline size_t VertexArray::getSize(void) const
    {
        return m_size;
    }

    inline void VertexArray::resize(size_t new_size)
    {
        if (new_size <= m_capacity)
        {
            m_size = new_size;
            return;
        }

        reserve(new_size);
        m_size = new_size;
    }

    inline void VertexArray::appendVertex(const Vertex &vertex)
    {
        if (m_size == m_capacity)
            reserve(m_capacity * 2);

        assert(m_size < m_capacity);
        m_data[m_size++] = vertex;
    }

    inline Vertex &VertexArray::operator[](size_t index)
    {
        assert(index < m_size);
        return m_data[index];
    }

    inline const Vertex &VertexArray::operator[](size_t index) const
    {
        assert(index < m_size);
        return m_data[index];
    }

    inline void VertexArray::reserve(size_t new_capacity)
    {
        assert(new_capacity > m_capacity);

        Vertex *new_data = new Vertex[new_capacity];
        for (size_t ind = 0; ind < m_size; ++ind)
        {
            new_data[ind] = m_data[ind];
        }
        delete[] m_data;

        m_data = new_data;
        m_capacity = new_capacity;
    }

} // namespace plug

#endif  // PLUG_GRAPHICS_VERTEX_ARRAY_HPP

