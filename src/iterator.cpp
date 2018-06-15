/*

File: iterator.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree, Jacob Bickle

https://github.com/AlexanderJDupree/LinkedListsCPP

*/

// Iterator implementation

#ifndef ITERATOR_TPP
#define ITERATOR_TPP

#include "iterator.hpp"

/*******************************************************************************
iterator_base
*******************************************************************************/

template <typename T>
iterator_base<T>::iterator_base(pointer ptr) : node(ptr) {}

template <typename T>
typename iterator_base<T>::self_type& iterator_base<T>::operator++()
{
    node = node->Next();
    return *this;
}

template <typename T>
typename iterator_base<T>::self_type iterator_base<T>::operator++(int)
{
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <typename T>
typename iterator_base<T>::reference iterator_base<T>::operator*()
{
    return *node->Data();
}

template <typename T>
bool iterator_base<T>::operator==(const self_type& rhs) const
{
    return node == rhs.node;
}

template <typename T>
bool iterator_base<T>::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

/*******************************************************************************
const_forward_iterator
*******************************************************************************/

template <typename T>
typename const_forward_iterator<T>::self_type&
const_forward_iterator<T>::operator+=(size_t n)
{
    while (n > 0 &&  this->node != nullptr)
    {
        ++(*this);
        --n;
    }
    return *this;
}

#endif // ITERATOR_TPP