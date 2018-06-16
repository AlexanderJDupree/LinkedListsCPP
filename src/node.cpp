/*

File: node.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree, Jacob Bickle

https://github.com/AlexanderJDupree/LinkedListsCPP

*/

// Implementation for Node class

#ifndef NODE_TPP
#define NODE_TPP

#include "node.hpp"

template <typename T>
Node<T>::Node() : _data(new T()), _next(nullptr) {}

template <typename T>
Node<T>::Node(const Node& origin)
    : _data(new T(*origin._data)), _next(origin._next) {}

template <typename T>
Node<T>::Node(const T& value) : _data(new T(value)), _next (nullptr) {}

template <typename T>
Node<T>::~Node()
{
    delete _data;
}

// Inspectors
template <typename T>
T* Node<T>::data() const
{
    return _data;
}

template <typename T>
Node<T>* Node<T>::next() const
{
    return _next;
}

// Mutators
template <typename T>
Node<T>* Node<T>::data(const T& value)
{
    delete _data;
    this->_data = new T(value);
    return this;
}

template <typename T>
Node<T>* Node<T>::next(Node* node)
{
    _next = node;
    return this;
}

#endif // NODE_TPP
