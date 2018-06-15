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

/*******************************************************************************
NODE.HPP
*******************************************************************************/

#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
public:

    /* Constructors */
    
    // Default
    Node();

    // Copy
    Node(const Node& origin);

    // Value
    explicit Node(const T& value);

    // Destructor
    ~Node();

    /* Inspectors */
    T* Data() const;
    Node* Next() const;

    /* Mutators */
    Node* Data(const T& value);
    Node* Next(Node* node);


private:

    T* data;
    Node* next;
};

// NODE IMPLEMENTATION

#ifndef NODE_TPP
#define NODE_TPP

template <typename T>
Node<T>::Node() : data(new T()), next(nullptr) {}

template <typename T>
Node<T>::Node(const Node& origin)
    : data(new T(*origin.data)), next(origin.next) {}

template <typename T>
Node<T>::Node(const T& value) : data(new T(value)), next (nullptr) {}

template <typename T>
Node<T>::~Node()
{
    delete data;
}

// Inspectors
template <typename T>
T* Node<T>::Data() const
{
    return data;
}

template <typename T>
Node<T>* Node<T>::Next() const
{
    return next;
}

// Mutators
template <typename T>
Node<T>* Node<T>::Data(const T& value)
{
    delete data;
    this->data = new T(value);
    return this;
}

template <typename T>
Node<T>* Node<T>::Next(Node* node)
{
    next = node;
    return this;
}

#endif // NODE_TPP
#endif // NODE_H

/*******************************************************************************
ITERATOR.HPP
*******************************************************************************/

#ifndef ITERATORS_H
#define ITERATORS_H

#include <iterator>

// Forward Declaration
template <typename T> class LinkedList;

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

    friend class LinkedList<T>;

protected:

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

    self_type& operator+=(size_t n);

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

// Iterator implementation

#ifndef ITERATOR_TPP
#define ITERATOR_TPP

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
#endif // ITERATORS_H

/*******************************************************************************
LINKEDLIST.HPP
*******************************************************************************/

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

// Linked List implementations
#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

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
typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const
{
    return const_iterator(head);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin()
{
    return iterator(head);
} 

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cend() const
{
    // Prevents segmentation fault if attempt to get tails next node if tail is
    // is a nullptr. Since tail will always point to a nullptr we can just 
    // return an iterator to a nullptr
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

    temp->Next(head);
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
    if (this->empty())
    {
        push_front(data);
        return;
    }

    node_pointer temp = new Node<T>(data);

    tail->Next(temp);
    tail = temp;

    return;
}

template<typename T>
void LinkedList<T>::pop_front()
{
    if (empty()) { return; }

    node_pointer next = head->Next();

    delete head;
    head = next;

    return;
}

template<typename T>
T& LinkedList<T>::pop_front(reference out_data)
{
    if (empty()) { return out_data; }

    node_pointer next = head->Next();
    out_data = *head->Data();

    delete head;
    head = next;

    return out_data;
}

template<typename T>
void LinkedList<T>::pop_back()
{
    if (empty()) { return; }

    node_pointer previous = head; 

    while (previous->Next() != tail)
    {
        previous = previous->Next();
    }
    delete tail;

    previous->Next(nullptr);
    tail = previous;

    return; 

}

template<typename T>
T& LinkedList<T>::pop_back(reference out_data)
{
    if (empty()) { return out_data; }

    node_pointer previous = head; 

    while (previous->Next() != tail)
    {
        previous = previous->Next();
    }
    out_data = *tail->Data();
    delete tail;

    previous->Next(nullptr);
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
    newNode->Next(position.node->Next());

    position.node->Next(newNode);

    if(tail->Next() == newNode)
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
        while (previous->Next() != position.node)
        {
            previous = previous->Next();
        }
    }

    previous->Next(position.node->Next());

    node_pointer temp = position.node;

    if (temp == head)
    {
        head = head->Next();
    }

    position = iterator(previous->Next());

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
        head = head->Next();
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
    if (current->Next() != nullptr)
    {
        reverse_links(current->Next(), current);
    }

    current->Next(previous);

    return;
}

template <typename T>
template <class Comparator>
void LinkedList<T>::merge_sort(node_pointer& begin, Comparator compare)
{
    // Base case
    if(begin == nullptr || begin->Next() == nullptr)
    {
        return;
    }

    node_pointer left = begin;
    node_pointer right = begin->Next();

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
    while((right = right->Next()) != nullptr)
    {
        if (right->Next() != nullptr)
        {
            // left travels through the list only one link at a time
            left = left->Next();
            right = right->Next();
        }
    }
    // Left is at the midpoint of the list
    right = left->Next();
    left->Next(nullptr);
}

template <typename T>
template <class Comparator>
Node<T>* LinkedList<T>::merge(node_pointer left, node_pointer right, Comparator compare)
{
    node_pointer begin = nullptr;

    if(left == nullptr) { return right; }
    else if (right == nullptr) { return left; }

    if(compare(*left->Data(), *right->Data()))
    {
        begin = left;
        begin->Next(merge(left->Next(), right, compare));
    }
    else
    {
        begin = right;
        begin->Next(merge(left, right->Next(), compare));
    }
    return begin;
}

#endif // LINKED_LIST_TPP
#endif // LINKED_LIST_H
