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

#include "node.hpp"
#include "iterator.hpp"

template<typename T>
class LinkedList : public forward_iterator<T>
{
public:

    /* Type Defs */
    typedef forward_iterator<T> iterator;
    typedef const_forward_iterator<T> const_iterator;

    /* Constructors */

    // Default
    LinkedList();

    // Fill
    LinkedList(size_t count, const T& data);

    // Copy
    explicit LinkedList(const LinkedList<T>& origin);

    // Destructor
    ~LinkedList();

    /* Iterators */
    const_iterator cbegin() const;
    iterator begin();

    const_iterator cend() const;
    iterator end();

    /* Modifiers */
    void push_front(const T& data);
    void push_back(const T& data);
    void insert(LinkedList<T>::iterator pos, const T& data);
    void clear();

    /* Capacity */
    bool empty() const;
    size_t size() const;

    /* Operator Overloads */
    inline bool operator==(const LinkedList<T>& rhs) const;
    inline bool operator!=(const LinkedList<T>& rhs) const;

private:

    Node<T>* head;
    Node<T>* tail;

};

#include "linkedList.cpp"

#endif // LINKED_LIST_H
