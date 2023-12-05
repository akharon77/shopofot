#ifndef LIST_HPP
#define LIST_HPP

#include <stdint.h>

#include "list/buf_list.hpp"

template<typename T>
class List
{
public:
    int32_t      m_size;

    int32_t       m_dummy_head;
    BufferList<T> m_free_buf;

    List();
    ~List();

    // TODO
    List& operator = (const List &rhs) = delete;
    List(const List &rhs) = delete;

    int32_t     InsertBefore (const T &val, int32_t anch);
    int32_t     InsertAfter  (const T &val, int32_t anch);
    void        Erase        (              int32_t anch);

    int32_t     PushBack     (const T &val);
    int32_t     PushFront    (const T &val);

    void        PopBack      ();
    void        PopFront     ();

    int32_t    GetSize      () const;

    int32_t     GetTail      () const;

    inline Node<T>* Get(int32_t anch) const
    {
        return m_free_buf.Get(anch);
    }
         
    inline int32_t GetHead() const
    {
        return m_free_buf.m_buf[m_dummy_head].next;
    }
};

template<typename T>
List<T>::List() :
    m_free_buf(1)
{
    m_dummy_head = m_free_buf.Pop();

    m_free_buf.m_buf[m_dummy_head] = Node<T>
        {
            T(),
            m_dummy_head,
            m_dummy_head             
        };

    m_size = 0;
}

template<typename T>
List<T>::~List()
{
    m_dummy_head = -1;
    m_size       =  0;
}

template<typename T>
int32_t List<T>::InsertBefore(const T &val, int32_t anch)
{
    int32_t npos = m_free_buf.Pop();

    int32_t anch_prev = m_free_buf.m_buf[anch].prev;

    m_free_buf.m_buf[npos] = Node<T>
        {
            val,
            anch,
            anch_prev
        };

    m_free_buf.m_buf[anch_prev].next = npos;
    m_free_buf.m_buf[anch     ].prev = npos;
    
    ++m_size;

    return npos;
}

template<typename T>
int32_t List<T>::InsertAfter(const T &val, int32_t anch)
{
    return InsertBefore(val, m_free_buf.m_buf[anch].next);
}

template<typename T>
void List<T>::Erase(int32_t anch)
{
    int32_t prev_anch = m_free_buf.m_buf[anch].prev,
            next_anch = m_free_buf.m_buf[anch].next;

    m_free_buf.m_buf[prev_anch].next = next_anch;
    m_free_buf.m_buf[next_anch].prev = prev_anch;

    m_free_buf.Add(anch);

    --m_size;
}

template<typename T>
int32_t List<T>::PushBack (const T &val)
{
    return InsertBefore(val, m_dummy_head);
}

template<typename T>
int32_t List<T>::PushFront(const T &val)
{
    return InsertAfter (val, m_dummy_head);
}

template<typename T>
void List<T>::PopBack()
{
    Erase(GetTail());
}

template<typename T>
void List<T>::PopFront()
{
    Erase(GetHead());
}

// int32_t ListGetHead(List *lst)
// {
//     ASSERT(lst != NULL);
//     return lst->free_buf->buf[lst->dummy_head].next;
// }

template<typename T>
int32_t List<T>::GetTail() const
{
    return m_free_buf.m_buf[m_dummy_head].prev;
}

template<typename T>
int32_t List<T>::GetSize() const
{
    return m_size;
}

// Node* ListGet(List *lst, int32_t anch)
// {
//     return BufferListGet(lst->free_buf, anch);
// }

#endif  // LIST_HPP

