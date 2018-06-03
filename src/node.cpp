// Implementation for Node class

#ifndef NODE_TPP
#define NODE_TPP

#include "node.hpp"

template <typename T>
Node<T>::Node() : data(nullptr), next(nullptr) {}

template <typename T>
Node<T>::~Node()
{
    delete data;
}

// Inspectors
template <typename T>
const T* Node<T>::Data() const
{
    return data;
}

template <typename T>
Node<T>* Node<T>::Next() 
{
    return next;
}

// Mutators
template <typename T>
Node<T>* Node<T>::Data(const T& data)
{
    delete this->data;
    *this->data = data;
    return this;
}

template <typename T>
Node<T>* Node<T>::Next(Node* node)
{
    next = node;
    return this;
}

#endif // NODE_TPP