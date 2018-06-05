// Linked List implementations

#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "linkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

// Iterator Class
template <typename T>
LinkedList<T>::iterator::iterator(Node<T>* ptr) : node(ptr) {}

template <typename T>
T& LinkedList<T>::iterator::operator*() 
{
    return *node->Data();
}

// End Iterator Class

// Iterators
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() const
{
    return iterator(head);
} 

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() const
{
    return iterator(tail);
} 

// Modifiers
template <typename T>
void LinkedList<T>::push_front(const T& data)
{
    Node<T>* temp = new Node<T>(data);
    temp->Next(head);
    head = temp;
    return;
}

// Capacity functions
template <typename T>
bool LinkedList<T>::empty() const
{
    return !(head);
}

#endif // LINKED_LIST_TPP