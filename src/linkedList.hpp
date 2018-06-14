/*******************************************************************************
* File: linkedList.hpp
*
* Description: 
* 
* Compiler: GNU GCC 5.4.0
*
* Date: 2018 - 05 - 31
*******************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <type_traits>
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
    explicit LinkedList(const LinkedList<value_type>& origin);

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
    void pop_front(T& overwright);
    void pop_back();
    void pop_back(T& overwright);
    void insert(iterator position, const_reference data);
    iterator erase(iterator& position);
    iterator erase(iterator& first, iterator& last);
    void clear();

    /* Capacity */
    bool empty() const;
    size_type size() const;

    /* Operator Overloads */
    inline bool operator==(const LinkedList<value_type>& rhs) const;
    inline bool operator!=(const LinkedList<value_type>& rhs) const;



private:

    node_pointer head;
    node_pointer tail;

};

#include "linkedList.cpp"

#endif // LINKED_LIST_H
