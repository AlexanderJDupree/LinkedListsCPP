/*******************************************************************************
* File: linkedList.h
*
* Description: 
* 
* Compiler: GNU GCC 5.4.0
*
* Date: 2018 - 05 - 31
*******************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iterator>
#include "node.hpp"

template<typename T>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList() {}

    class iterator
    {
    public:

        iterator(Node<T>* ptr);

        T& operator*();

    private:
       Node<T>* node;
    };

    // Iterators
    iterator begin() const;
    iterator end() const;

    // Modifiers
    void push_front(const T& data);

    // Capacity functions
    bool empty() const;


private:

    Node<T>* head;
    Node<T>* tail;

};

#include "linkedList.cpp"

#endif // LINKED_LIST_H