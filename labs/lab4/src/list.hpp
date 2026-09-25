#pragma once
#include <iostream>
#include <cstddef>
#include "circle.hpp"

class List
{
private:
    class Node
    {
    public:
        Node *pPrev;
        Node *pNext;
        Circle m_Data;

        Node();
        Node(Node *prev, const Circle *pc);
        ~Node();
    };

    Node Head;
    Node Tail;
    size_t m_size;

public:
    List();
    List(const List &other);
    List& operator=(const List &other);
    ~List();

    void push_front(const Circle &c);
    void push_back(const Circle &c);

    bool remove_first(const Circle &c);
    size_t remove_all(const Circle &c);
    void clear();

    size_t size() const;
    bool empty() const;

    void sort_by_area();

    friend std::ostream& operator<<(std::ostream &os, const List &list);
    friend std::istream& operator>>(std::istream &is, List &list);
};
