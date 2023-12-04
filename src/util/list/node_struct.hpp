#ifndef LIST_NODE_STRUCT_H
#define LIST_NODE_STRUCT_H

#include <stdint.h>

template<typename T>
struct Node
{
    T val;

    int32_t next;
    int32_t prev;
};

#endif  // LIST_NODE_STRUCT_H
