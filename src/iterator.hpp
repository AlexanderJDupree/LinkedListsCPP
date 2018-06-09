/*******************************************************************************
* File: iterator.cpp
*
* Description: 
*
* Compiler: GNU GCC 5.4.0
*
* Date: 2018 - 06 - 07
*******************************************************************************/

#ifndef ITERATORS_H
#define ITERATORS_H

#include <iterator>
#include "node.hpp"

template <typename T>
class iterator_base
{
public:
    // Typedefs to make iterators STL friendly
    typedef T value_type;
    typedef T& reference;
    typedef Node<T>* pointer;
    typedef iterator_base self_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::input_iterator_tag iterator_category;

    // Constructors
    iterator_base() : node(nullptr) {};
    explicit iterator_base(pointer ptr);

    // operator overloads
    self_type& operator++(); // Prefix ++
    self_type operator++(int); // Postfix ++
    reference operator*();

    bool operator==(const self_type& rhs) const;
    bool operator!=(const self_type& rhs) const;

public:
    pointer node;
};

template <typename T>
class const_forward_iterator : public iterator_base<T>
{   
public:
    typedef T value_type;
    typedef const T& reference; // Const reference to data member
    typedef Node<T>* pointer;
    typedef const_forward_iterator self_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    const_forward_iterator() : iterator_base<T>() {}
    explicit const_forward_iterator(pointer ptr) : iterator_base<T>(ptr) {}
};


template <typename T>
class forward_iterator : public const_forward_iterator<T>
{   
public:
    typedef T value_type;
    typedef T& reference;
    typedef Node<T>* pointer;
    typedef forward_iterator self_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    forward_iterator() : const_forward_iterator<T>() {}
    explicit forward_iterator(pointer ptr) 
        : const_forward_iterator<T>(ptr) {}
};


#include "iterator.cpp"

#endif // ITERATORS_H