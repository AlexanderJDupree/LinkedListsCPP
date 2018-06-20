/*

File: LinkedList.cpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree, Jacob Bickle

https://github.com/AlexanderJDupree/LinkedListsCPP

*/

#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "linkedList.hpp"

/*******************************************************************************
CONSTRUCTORS
*******************************************************************************/

// Default
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}
// Fill
template <typename T>
LinkedList<T>::LinkedList(size_type count, const_reference data) : LinkedList()
{
    while (count > 0)
    {
        push_front(data);
        --count;
    }
}

// Range
template <typename T>
template <typename InputIterator, typename ::std::enable_if< ::std::is_constructible
         < T, decltype(*::std::declval<InputIterator>()) >::value >::type* >
LinkedList<T>::LinkedList(InputIterator begin, InputIterator end) : LinkedList()
{
    for (;begin != end; ++begin)
    {
        push_back(*begin);
    }
}



// Copy
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<value_type>& origin) : LinkedList()
{
    LinkedList<T>::const_iterator it;
    for (it = origin.cbegin(); it != origin.cend(); ++it)
    {
        push_back(*it);
    }
}

// Initializer List
template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<value_type> init) : LinkedList()
{
    typename std::initializer_list<T>::iterator it;
    for(it = init.begin(); it != init.end(); ++it)
    {
        push_back(*it);
    }
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() 
{
    clear();
}

/*******************************************************************************
ITERATORS
*******************************************************************************/

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const noexcept
{
    return const_iterator(head);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::begin() const
{
    return const_iterator(head);
} 

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin()
{
    return iterator(head);
} 

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cend() const noexcept
{
    return const_iterator(nullptr);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::end() const
{
    return const_iterator(nullptr);
} 

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end()
{
    return iterator(nullptr);
} 

/*******************************************************************************
MODIFIERS
*******************************************************************************/

template <typename T>
void LinkedList<T>::push_front(const_reference data)
{
    node_pointer temp = new Node<T>(data);

    temp->next(head);
    head = temp;

    if (tail == nullptr)
    {
        tail = head;
    }

    return;
}

template <typename T>
void LinkedList<T>::push_back(const_reference data)
{
    if (empty())
    {
        push_front(data);
        return;
    }

    node_pointer temp = new Node<T>(data);

    tail->next(temp);
    tail = temp;

    return;
}

template<typename T>
void LinkedList<T>::pop_front()
{
    if (empty()) { return; }

    node_pointer next = head->next();

    delete head;
    head = next;

    return;
}

template<typename T>
T& LinkedList<T>::pop_front(reference out_data)
{
    if (empty()) { return out_data; }

    node_pointer next = head->next();
    out_data = *head->data();

    delete head;
    head = next;

    return out_data;
}

template<typename T>
void LinkedList<T>::pop_back()
{
    if (empty()) { return; }

    node_pointer previous = head; 

    while (previous->next() != tail)
    {
        previous = previous->next();
    }
    delete tail;

    previous->next(nullptr);
    tail = previous;

    return; 

}

template<typename T>
T& LinkedList<T>::pop_back(reference out_data)
{
    if (empty()) { return out_data; }

    node_pointer previous = head; 

    while (previous->next() != tail)
    {
        previous = previous->next();
    }
    out_data = *tail->data();
    delete tail;

    previous->next(nullptr);
    tail = previous;

    return out_data; 
}

template<typename T>
void LinkedList<T>::insert(const_iterator& position, const_reference data)
{
    if(empty())
    {
        push_front(data);
        position = iterator(head); 
        return;
    }

    node_pointer newNode = new Node<T>(data);
    newNode->next(position.node->next());

    position.node->next(newNode);

    if(tail->next() == newNode)
    {
        tail = newNode;
    }
 
    return;
}

template <typename T>
void LinkedList<T>::insert(const_iterator position, size_type n, const_reference data)
{
    LinkedList<value_type> temp(n, data);
    insert(position, temp.begin(), temp.end());
    return;
}

template <typename T>
template <typename InputIterator>
void LinkedList<T>::insert(const_iterator position, InputIterator begin, InputIterator end)
{
    if (empty())
    {
        push_front(*begin++);
        position = iterator(head);
    }

    for(;begin != end; ++begin)
    {
        insert(position, *begin);
        ++position;
    }
    return;
}

template<typename T>
typename LinkedList<T>::iterator 
LinkedList<T>::erase(iterator& position)
{
    if (empty()) { return position; }

    node_pointer previous = head;

    if (previous != position.node)
    {
        while (previous->next() != position.node)
        {
            previous = previous->next();
        }
    }

    previous->next(position.node->next());

    node_pointer temp = position.node;

    if (temp == head)
    {
        head = head->next();
    }

    position = iterator(previous->next());

    delete temp;

    return position;
}

template<typename T>
typename LinkedList<T>::iterator 
LinkedList<T>::erase(iterator& first, iterator& last)
{
    while (first != last)
    {
        first = erase(first);
    }

    return first;
}


template <typename T>
void LinkedList<T>::clear()
{
    if (empty())
    {
        return;
    }

    node_pointer previous = head;

    while (head != nullptr)
    {
        previous = head;
        head = head->next();
        delete previous;
    }

    return;
}

/*******************************************************************************
CAPACITY
*******************************************************************************/ 

template <typename T>
bool LinkedList<T>::empty() const
{
    return !(head);
}

template <typename T>
size_t LinkedList<T>::size() const
{
    size_type SIZE = 0;

    for(const_iterator it = cbegin(); it != cend(); ++it)
    {
        ++SIZE;
    }

    return SIZE;
}

/*******************************************************************************
Operations
*******************************************************************************/ 

template <typename T>
void LinkedList<T>::reverse() noexcept
{
    if (empty()) { return; }

    reverse_links(head, nullptr);

    std::swap(head, tail);

    return;
}

template <typename T>
void LinkedList<T>::remove(const_reference target)
{
    remove_if([&target] (const_reference value) { return value == target; });
    return;
}

template <typename T>
template <class Predicate>
void LinkedList<T>::remove_if(Predicate pred)
{
    iterator it = begin();
    while(it != end())
    {
        pred(*it) ? erase(it) : ++it;
    }
    return;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::find(const_reference target)
{
    return find_if([&target](const_reference value){return value == target;});
}

template <typename T>
template <class Predicate>
typename LinkedList<T>::iterator LinkedList<T>::find_if(Predicate pred)
{
    iterator it = begin();
    while(it != end())
    {
        if(pred(*it))
        {
            return it;
        }
        ++it;
    }
    return it;
}

template <typename T>
void LinkedList<T>::unique()
{
    std::unordered_set<T> uniqueElements;
    iterator it = begin();
    while(it != end())
    {
        if (uniqueElements.find(*it) == uniqueElements.end())
        {
            uniqueElements.insert(*it);
            ++it;
        }
        else
        {
            it = erase(it);
        }
    }
    return;
}

template <typename T>
template <class Comparator>
void LinkedList<T>::sort(Comparator compare)
{
    merge_sort(head, compare);

    return;
}

template <typename T>
void LinkedList<T>::sort()
{
    sort([](const_reference val1, const_reference val2){return val1 < val2;});
}

/*******************************************************************************
OPERATOR OVERLOADS
*******************************************************************************/

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<value_type>& rhs) const
{
    if (size() != rhs.size()) { return false; }

    LinkedList<T>::const_iterator left = cbegin();
    LinkedList<T>::const_iterator right = rhs.cbegin();

    while(left != cend() && right != rhs.cend())
    {
        if (*left != *right) { return false; }
        ++left;
        ++right;
    }

    return true;
}

template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<value_type>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<value_type> list)
{
    swap(*this, list);

    return *this;
}

/*******************************************************************************
*******************************************************************************/

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& newList, LinkedList<T>& oldList) noexcept
{
    // Enables ADL
    using std::swap;
    
    // Swap pointers, reassigns ownership
    swap(newList.head, oldList.head);
    swap(newList.tail, oldList.tail);
    return;
}

template <typename T>
void LinkedList<T>::reverse_links(node_pointer current, node_pointer previous) noexcept
{
    if (current->next() != nullptr)
    {
        reverse_links(current->next(), current);
    }

    current->next(previous);

    return;
}

template <typename T>
template <class Comparator>
void LinkedList<T>::merge_sort(node_pointer& begin, Comparator compare)
{
    // Base case
    if(begin == nullptr || begin->next() == nullptr)
    {
        return;
    }

    node_pointer left = begin;
    node_pointer right = begin->next();

    // Split the list in half, break the links from left -> right
    split(left, right);

    left = begin;

    // Recursively break the links and split the list in half
    merge_sort(left, compare);
    merge_sort(right, compare);

    // Relink the list together in sorted order
    begin = merge(left, right, compare);

    return;
}

template <typename T>
void LinkedList<T>::split(node_pointer& left, node_pointer& right)
{
    // right travels through the list two links at a time
    while((right = right->next()) != nullptr)
    {
        if (right->next() != nullptr)
        {
            // left travels through the list only one link at a time
            left = left->next();
            right = right->next();
        }
    }
    // Left is at the midpoint of the list
    right = left->next();
    left->next(nullptr);
}

template <typename T>
template <class Comparator>
Node<T>* LinkedList<T>::merge(node_pointer left, node_pointer right, Comparator compare)
{
    node_pointer begin = nullptr;

    if(left == nullptr) { return right; }
    else if (right == nullptr) { return left; }

    if(compare(*left->data(), *right->data()))
    {
        begin = left;
        begin->next(merge(left->next(), right, compare));
    }
    else
    {
        begin = right;
        begin->next(merge(left, right->next(), compare));
    }
    return begin;
}


#endif // LINKED_LIST_TPP
