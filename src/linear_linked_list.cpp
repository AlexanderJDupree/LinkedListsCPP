/*
 
 File: linear_linked_list.cpp

 Brief: Implementation file for the linear_linked_list data structure

 Copyright (c) 2018 Alexander DuPree

 This software is released as open source through the MIT License

 Authors: Alexander DuPree

 https://github.com/AlexanderJDupree/LinkedListsCPP

*/

#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "linear_linked_list.hpp"

/****** CONSTRUCTORS ******/

// default constructor
template <typename T>
linear_linked_list<T>::linear_linked_list() 
    : head(nullptr), tail(nullptr), _size(0) {}

// ranged based constructor
template <typename T>
template <class InputIterator>
linear_linked_list<T>::linear_linked_list(InputIterator begin, InputIterator end) 
    : linear_linked_list()
{
    for(; begin != end; ++begin)
    {
        push_back(*begin);
    }
}

// Initializer List
template <typename T>
linear_linked_list<T>::linear_linked_list(std::initializer_list<value_type> init)
    : linear_linked_list()
{
    for (const_reference element : init)
    {
        push_back(element);
    }
}

// Copy constructor
template <typename T>
linear_linked_list<T>::linear_linked_list(const self_type& origin) 
    : linear_linked_list()
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
linear_linked_list<T>& linear_linked_list<T>::push_front(const_reference& data)
{
    Node* temp = new Node(data, head);
    head = temp;

    if (tail == nullptr)
    {
        tail = head;
    }

    ++_size;
    return *this;
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_back(const_reference& data)
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
T& linear_linked_list<T>::pop_front(reference out_param)
{
    if(!empty())
    {
        out_param = head->data;

        pop_front();
    }
        
    return out_param;
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::clear()
{
    if(empty())
    {
        return *this;
    }

    // clear_list is a recursive function that deletes each node of the list
    clear_list(head);

    _size = 0;

    tail = nullptr;

    return *this;
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
    current = nullptr;

    return;
}

template <typename T>
int linear_linked_list<T>::remove(const_reference target)
{
    // lambda catches target and compares it to each element in the list
    return remove_if([&target](T& sample){ return target == sample; });
}

template <typename T>
template <class Predicate>
int linear_linked_list<T>::remove_if(Predicate&& pred)
{
    if (empty())
    {
        return 0;
    }
    
    return remove_if(pred, head);
}

template <typename T>
template <class Predicate>
int linear_linked_list<T>::remove_if(Predicate&& pred, Node*& current, Node* prev)
{
    // Base Case: Traversed the whole list
    if(current == nullptr)
    {
        return 0;
    }

    // Predicate fulfilled, remove this element
    if(pred(current->data))
    {

        // Edge case : element to be removed is the tail. 
        if (tail == current)
        {
            tail = prev;
        }

        prev = current;

        current = current->next;

        delete prev;

        --_size;

        return 1 + remove_if(pred, current, prev=current);
    }

    prev = current;

    return remove_if(pred, current->next, prev);
}

/****** CAPACITY ******/

template <typename T>
bool linear_linked_list<T>::empty() const
{
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
    return iterator(nullptr);
}

template <typename T>
typename linear_linked_list<T>::const_iterator 
linear_linked_list<T>::end() const
{
    return const_iterator(nullptr);
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
        if (*(left++) != *(right++))
        {
            return false;
        }
    }

    return true; // TODO test left and right are both end iterators
}

template <typename T>
bool linear_linked_list<T>::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
typename linear_linked_list<T>::self_type& 
linear_linked_list<T>::operator=(self_type copy)
{
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

    throw std::logic_error("Element access fail, null pointer");
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
typename linear_linked_list<T>::const_iterator
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
    // Iterators are equal if they point to the same memory address
    return node == rhs.node;
}

template <typename T>
bool linear_linked_list<T>::const_iterator::operator!=(const self_type& rhs) const
{
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
