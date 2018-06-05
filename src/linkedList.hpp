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
        // Typedefs to make iterator STL friendly
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef Node<T>* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
    
        // Constructors
        iterator() : node(nullptr) {}
        iterator(pointer ptr);

        // Operator overloads
        bool operator==(const self_type& rhs) const;
        bool operator!=(const self_type& rhs) const;
        self_type& operator++(); // Prefix ++ 
        self_type operator++(int); // Postfix ++
        reference operator*();

    private:
       pointer node;
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