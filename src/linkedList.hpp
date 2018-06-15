/*

File: LinkedList.hpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree, Jacob Bickle

https://github.com/AlexanderJDupree/LinkedListsCPP

*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <type_traits>
#include <algorithm>
#include <unordered_set>
#include "node.hpp"
#include "iterator.hpp"

template<typename T>
class LinkedList : public forward_iterator<T>
{
public:

    /* Type Defs */
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef forward_iterator<T> iterator;
    typedef const_forward_iterator<T> const_iterator;
    typedef Node<T>* node_pointer;

    /* Constructors */

    // Default
    LinkedList();

    // Fill
    LinkedList(size_type count, const_reference data);

    // Range
    template <typename InputIterator, typename ::std::enable_if< ::std::is_constructible
             < T, decltype(*::std::declval<InputIterator>()) >::value >::type* = nullptr >
    LinkedList(InputIterator begin, InputIterator end);

    // Copy
    LinkedList(const LinkedList<value_type>& origin);

    // Initializer List
    explicit LinkedList(std::initializer_list<value_type> init);

    // Destructor
    ~LinkedList();

    /* Iterators */
    const_iterator cbegin() const;
    iterator begin();

    const_iterator cend() const;
    iterator end();

    /* Modifiers */
    void push_front(const_reference data);
    void push_back(const_reference data);
    
    void pop_front();
    reference pop_front(reference out_data);
    void pop_back();
    reference pop_back(reference out_data);
    
    void insert(const_iterator& position, const_reference data);
    void insert(const_iterator position, size_type n, const_reference data);
    template <typename InputIterator>
    void insert(const_iterator position, InputIterator begin, InputIterator end);

    iterator erase(iterator& position);
    iterator erase(iterator& first, iterator& last);
    
    void clear();

    /* Capacity */
    bool empty() const;
    size_type size() const;

    /* Operations */
    void reverse() noexcept;

    void remove(const_reference target);
    template <class Predicate>
    void remove_if(Predicate pred);

    iterator find(const_reference target);
    template <class Predicate>
    iterator find_if(Predicate pred);
    
    void unique();

    template <class Comparator>
    void sort(Comparator compare);
    void sort();

    /* Operator Overloads */
    inline bool operator==(const LinkedList<value_type>& rhs) const;
    inline bool operator!=(const LinkedList<value_type>& rhs) const;
    LinkedList<value_type>& operator=(LinkedList<value_type> list);

    /* Swap */
    void swap(LinkedList<value_type>& newList, LinkedList<value_type>& oldList) noexcept;



private:

    node_pointer head;
    node_pointer tail;

    /* Helper functions */
    void reverse_links(node_pointer current, node_pointer previous) noexcept;

    template <class Comparator>
    void merge_sort(node_pointer& begin, Comparator compare);

    void split(node_pointer& left, node_pointer& right);

    template <class Comparator> 
    node_pointer merge(node_pointer left, node_pointer right, Comparator compare);

};

#include "linkedList.cpp"

#endif // LINKED_LIST_H
