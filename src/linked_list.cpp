/*
File: linked_list.cpp

Description: Implementation for templated linear_linked_list class. Defines
             methods for modifiers, capacity checks, and iteration of the 
             linear_linked_list data structure.

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "linked_list.h"

/****** CONSTRUCTORS ******/

// default constructor
template <typename T>
linear_linked_list<T>::linear_linked_list() 
    : head(NULL), tail(NULL), _size(0) {}

// ranged based constructor
template <typename T>
template <class InputIterator>
linear_linked_list<T>::linear_linked_list(InputIterator begin, InputIterator end) 
    : head(NULL), tail(NULL), _size(0)
{
    for(; begin != end; ++begin)
    {
        push_back(*begin);
    }
}

// Initializer List
template <typename T>
linear_linked_list<T>::linear_linked_list(std::initializer_list<value_type> init)
    : head(NULL), tail(NULL), _size(0)
{
    for (const_reference element : init)
    {
        push_back(element);
    }
}

// Copy constructor
template <typename T>
linear_linked_list<T>::linear_linked_list(const self_type& origin) 
    : head(NULL), tail(NULL), _size(0)
{
    const_iterator it;
    for (it = origin.begin(); it != origin.end(); ++it)
    {
        push_back(*it);
    }
}

// Destructor
template <typename T>
linear_linked_list<T>::~linear_linked_list()
{
    clear();
}

/****** MODIFIERS ******/

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_front(const_reference data)
{
    Node* temp = new Node(data, head);
    head = temp;

    if (tail == NULL)
    {
        tail = head;
    }

    ++_size;
    return *this;
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_back(const_reference data)
{
    if(empty())
    {
        return push_front(data);
    }

    Node* temp = new Node(data);

    tail->next = temp;
    tail = temp;

    ++_size;
    return *this;
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::pop_front()
{
    if (empty())
    {
        return *this;
    }

    Node* temp = head->next;

    // Edge case, there is only one element in the list
    if (tail == head)
    {
        tail = temp;
    }

    delete head;

    head = temp;

    --_size;

    return *this;
    
}

template <typename T>
void linear_linked_list<T>::clear()
{
    if(empty())
    {
        return;
    }

    // clear_list is a recursive function that deletes each node of the list
    clear_list(head);
    _size = 0;
    tail = NULL;
    return;
}

template <typename T>
void linear_linked_list<T>::clear_list(Node*& current)
{
    // While the current node pointer is not at the end of the list
    if (current != tail)
    {
        // Recursive call to travel to the end of the list
        clear_list(current->next);
    }

    // Deletes the current node as the stack unwinds
    delete current;
    current = NULL;

    return;
}

template <typename T>
template <class Predicate>
bool linear_linked_list<T>::remove_if(Predicate pred)
{
    if (empty())
    {
        return false;
    }

    if(pred(head->data))
    {
        pop_front();
        return true;
    }

    return remove_if(pred, head);
}

template <typename T>
template <class Predicate>
bool linear_linked_list<T>::remove_if(Predicate pred, Node* current)
{
    // Base case: no element in the list fulfills the predicate
    if(current == tail)
    {
        return false;
    }

    // Predicate fulfilled, remove next element
    if(pred(current->next->data))
    {
        Node* temp = current->next;
        current->next = temp->next;

        if (tail == temp)
        {
            tail = current;
        }

        delete temp;

        --_size;

        return true;
    }

    return remove_if(pred, current->next);
}

/****** CAPACITY ******/

template <typename T>
bool linear_linked_list<T>::empty() const
{
    /*
    Because head is only NULL when the list is empty we can return the 
    logical NOT of head. This returns true iff head is NULL.
    */

    return !(head);
}
template <typename T>
typename linear_linked_list<T>::size_type linear_linked_list<T>::size() const
{
    return _size;
}

/****** ELEMENT ACCESS ******/

template <typename T>
T& linear_linked_list<T>::front() 
{
    throw_if_null(head);

    return head->data;
}

template <typename T>
const T& linear_linked_list<T>::front() const
{
    throw_if_null(head);

    return head->data;
}

template <typename T>
T& linear_linked_list<T>::back() 
{
    throw_if_null(tail);

    return tail->data;
}

template <typename T>
const T& linear_linked_list<T>::back() const
{
    throw_if_null(tail);

    return tail->data;
}


/****** ITERATORS ******/

template <typename T>
typename linear_linked_list<T>::iterator
linear_linked_list<T>::begin()
{
    return iterator(head);
}

template <typename T>
typename linear_linked_list<T>::const_iterator 
linear_linked_list<T>::begin() const
{
    return const_iterator(head);
}

template <typename T>
typename linear_linked_list<T>::iterator
linear_linked_list<T>::end()
{
    return iterator(NULL);
}

template <typename T>
typename linear_linked_list<T>::const_iterator 
linear_linked_list<T>::end() const
{
    return const_iterator(NULL);
}

/****** COMPARISON OPERATORS ******/

template <typename T>
bool linear_linked_list<T>::operator==(const self_type& rhs) const
{
    // Compare sizes first
    if (rhs.size() != size())
    {
        return false;
    }

    const_iterator left = begin();
    const_iterator right = rhs.begin();

    while(left != end() && right != rhs.end())
    {
        // If any element does not match then return false
        if (*left != *right)
        {
            return false;
        }
        ++left;
        ++right;
    }

    return left == end() && right == end();
}

template <typename T>
bool linear_linked_list<T>::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
typename linear_linked_list<T>::self_type& 
linear_linked_list<T>::operator=(const self_type& origin)
{
    // Create a copy of the list, if an exception is thrown then the state of 
    // original list and our list is unchanged
    linear_linked_list<T> copy(origin);

    // Swap ownership of resources with the copy
    swap(*this, copy);

    // As the copy goes out of scope it destructs with the old data
    return *this;
}

template <typename T>
void linear_linked_list<T>::swap(self_type& new_list, self_type& old_list)
{
    using std::swap;

    // Swaps pointers, reassigns ownership
    swap(new_list.head, old_list.head);
    swap(new_list.tail, old_list.tail);
    swap(new_list._size, old_list._size);
    return;
}

template <typename T>
void linear_linked_list<T>::throw_if_null(Node* node) const
{
    if(node)
    {
        return;
    }

    throw std::logic_error("Element access fail, NULL pointer");
}

/*******************************************************************************
ITERATOR CLASS
*******************************************************************************/

/* Operator Overloads */
template <typename T>
typename linear_linked_list<T>::const_iterator& 
linear_linked_list<T>::const_iterator::operator++()
{
    // reassign node member to point to the next element in the container
    node = node->next;
    return *this;
}

template <typename T>
typename linear_linked_list<T>::const_iterator& 
linear_linked_list<T>::const_iterator::operator++(int)
{
    // Create a copy to satisfy postfix incrementation requirements
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <typename T>
bool linear_linked_list<T>::const_iterator::operator==(const self_type& rhs) const
{
    // Compare memory addresses, NOT the value of the data member
    return node == rhs.node;
}

template <typename T>
bool linear_linked_list<T>::const_iterator::operator!=(const self_type& rhs) const
{
    // return the logical NOT of the equality comparison
    return !(*this == rhs);
}

template <typename T>
typename linear_linked_list<T>::const_reference 
linear_linked_list<T>::const_iterator::operator*() const
{
    return node->data;
}

template <typename T>
typename linear_linked_list<T>::const_pointer
linear_linked_list<T>::const_iterator::operator->() const
{
    return &node->data;
}

template <typename T>
typename linear_linked_list<T>::reference
linear_linked_list<T>::iterator::operator*() 
{
    return this->node->data;
}

template <typename T>
typename linear_linked_list<T>::pointer
linear_linked_list<T>::iterator::operator->()
{
    return &this->node->data;
}

#endif //LINKED_LIST_CPP
