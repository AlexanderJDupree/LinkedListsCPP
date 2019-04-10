/*
 
 File: linear_linked_list.h

 Brief: Linear Linked List is a heap allocated, singularly linked, sequence 
        container. This data structure provides constant time insertion and 
        removal operations. However, random access is not supported. This 
        iplementation defines the standard push/pop/remove methods as well as 
        forward iterators traversal as well as higher order functions like
        for_each, and sort_by.

 Copyright (c) 2018 Alexander DuPree

 This software is released as open source through the MIT License

 Authors: Alexander DuPree

 v.2.1.0

 https://github.com/AlexanderJDupree/LinkedListsCPP

*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <utility> // std::move, std::exchange
#include <algorithm> // std::swap
#include <stdexcept> // std::logic_error
#include <initializer_list>  // std::initializer_list

template <typename T>
class linear_linked_list
{
  public:

    // forward declaration
    class const_forward_iterator;
    class forward_iterator;

    /* Type definitions */
    typedef T                      value_type;
    typedef T*                     pointer;
    typedef T&                     reference;
    typedef const T&               const_reference;
    typedef const T*               const_pointer;
    typedef size_t                 size_type;
    typedef forward_iterator       iterator;
    typedef const_forward_iterator const_iterator;
    typedef linear_linked_list<T>  self_type;

    /****** CONSTRUCTORS ******/

    // Default
    linear_linked_list();

    // Ranged based
    template <class InputIterator>
    linear_linked_list(InputIterator begin, InputIterator end);

    // Initializer List
    explicit linear_linked_list(std::initializer_list<value_type> init);

    // Copy Constructor
    linear_linked_list(const self_type& origin);

    // Move Constructor
    linear_linked_list(self_type&& origin);
   
    // Destructor
    ~linear_linked_list();
     
    /****** MODIFIERS ******/

    // TODO add push_front/back methods for lists and iterators

    // Adds an element to the front of the list
    self_type& push_front(T&& data);
    self_type& push_front(const_reference data);

    // Adds an element to the back of the list
    self_type& push_back(T&& data);
    self_type& push_back(const_reference data);

    // Removes the element at the front of the list
    self_type& pop_front();

    // Copies the front element onto the out_param and removes it
    reference pop_front(reference out_param);
    // NOTE: There is no pop_back method for the singly linked list, as the 
    // time complexity for pop_back is O(n). Therefore pop_front is encouraged

    // Removes each element from the container
    self_type& clear();

    // Reverses the order of elements
    self_type& reverse();

    // Sorts the list, defaults to ascending order
    self_type& sort();

    template <class Compare>
    self_type& sort(Compare&& comp);

    // Splits the list on the parameter and returns the split
    self_type split(const_iterator pos);

    // Merges list into this list
    self_type& merge(self_type& list);

    template <class Compare>
    self_type& merge(self_type& list, Compare&& comp);

    iterator erase_after(iterator pos);

    // Removes all items matching target, returns number of items removed
    int remove(const_reference target);

    // Removes the all items fullfilling the predicate function
    template <class Predicate>
    int remove_if(Predicate&& pred);

    /****** CAPACITY ******/

    // returns true if the list is empty
    bool empty() const;

    // returns length of list by recurring through the list. O(n) operation.
    size_type size() const;

    /****** ELEMENT ACCESS ******/

    // Returns a direct reference to the front element, throws if list is empty
    reference front();
    const_reference front() const;

    // Returns a direct reference to the rear element, throws if list is empty
    reference back();
    const_reference back() const;

    /****** ITERATORS ******/

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // Travels the list two nodes at a time to find the middle. O(n) complexity.
    iterator middle();
    const_iterator middle() const;

    /****** COMPARISON OPERATORS ******/

    // Compares sizes, then comapres each element of the list for equality
    bool operator==(const self_type& rhs) const;

    // returns the logical NOT of the equality comparison
    bool operator!=(const self_type& rhs) const;

    /****** COPY-ASSIGNMENT AND SWAP ******/

    // Swaps pointers to each other's resources. effectively reassigning 
    // ownership.
    void swap(self_type& origin);

    // creates a copy of the origin, then swaps ownership with the copy
    self_type& operator=(self_type copy);

  private:
    
    /* 
    @struct: Node

    @brief: Node is the atomic member for the linked list class. It stores
            the desired data and contains a pointer to the next node in the list.
    */
    struct Node
    {
        // Default values are default constructor and nullptr
        Node(const_reference value = value_type(), Node* next = nullptr) 
            : data(value), next(next) {}

        // rvalue constructor
        Node(T&& value, Node* next = nullptr)
            : data(std::forward<T>(value)), next(next) {}

        value_type data;
        Node* next;

    };

    Node* head;
    Node* tail;

    /* Recursive Functions */

    size_type size(Node* head) const;

    Node* middle(Node* head) const;
    Node* middle(Node* slow, Node* fast) const;

    template <class Predicate>
    const_iterator find_split(Node* head, Predicate&& pred);

    void clear_list(Node*& current);

    void reverse(Node* current, Node* prev=nullptr);

    template <class Compare>
    Node* merge(Node* self, Node* other, Compare&& comp);

    template <class Predicate>
    int remove_if(Predicate&& pred, Node*& current, Node* prev=nullptr);

    /* Subroutines */

    self_type& push_front(Node* node);
    self_type& push_back(Node* node);

    // Throws a logic error exception if the node* is nullptr
    void throw_if_null(Node* node) const;
    // TODO make custom null exception that can print out useful information

    public:

    /*
    @class: const_forward_iterator
    
    @brief: The const_forward_iterator is a read-only abstraction of the node 
            pointer. The const_forward_iterator provides methods for inspecting
            data, and incrementation. This iterator type does not support 
            decrementation or random access

            Because the iterator does not manage any resources and it's only 
            member is a pointer, we allow the use of the DEFAULT destructor, 
            copy constructor, and copy-assignment operator.
    */
    class const_forward_iterator
    {
      public:

        typedef const_forward_iterator  self_type;

        /* Constructors */

        // default constructor points the iterator to nullptr
        const_forward_iterator(Node* ptr = nullptr) : node(ptr) {}

        /* Operator Overloads */

        self_type& operator++(); // Prefix ++
        self_type operator++(int); // Postfix ++

        const_reference operator*() const;
        const_pointer operator->() const;

        // Iterators are equal if they point to the same memory address
        bool operator==(const self_type& rhs) const;
        bool operator!=(const self_type& rhs) const;

        friend linear_linked_list<T>;
      
      protected:

        Node* node;
    };

    /*
    @class: forward_iterator
    
    @brief: The forward_iterator is a read/write abstraction of the node 
            pointer. The forward_iterator inherits all methods from the 
            const_forward_iterator but overrides the reference operators
            to allow the client to mutate data
    */
    class forward_iterator : public const_forward_iterator
    {
      public:

        /* Type definitions */
        typedef forward_iterator    self_type;

        forward_iterator(Node* ptr = nullptr) : const_forward_iterator(ptr) {}

        reference operator*();

        pointer operator->();

    };
};

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

/****** CONSTRUCTORS ******/

// default constructor
template <typename T>
linear_linked_list<T>::linear_linked_list() 
    : head(nullptr), tail(nullptr) {}

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

// Move constructor
template <typename T>
linear_linked_list<T>::linear_linked_list(self_type&& origin)
    : linear_linked_list()
{
    origin.swap(*this);
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
    return push_front(new Node(data, head));
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_front(T&& data)
{
    return push_front(new Node(std::forward<T>(data), head));
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_front(Node* node)
{
    head = node;

    if (tail == nullptr)
    {
        tail = head;
    }

    return *this;
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_back(const_reference& data)
{
    return push_back(new Node(data));
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_back(T&& data)
{
    return push_back(new Node(std::forward<T>(data)));
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::push_back(Node* node)
{
    if(empty())
    {
        return push_front(node);
    }

    tail->next = node;
    tail = node;

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

    return *this;
}

template <typename T>
T& linear_linked_list<T>::pop_front(reference out_param)
{
    if(!empty())
    {
        out_param = std::move(head->data);

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
linear_linked_list<T>& linear_linked_list<T>::reverse()
{
    if(!empty())
    {
        reverse(head);

        std::swap(head, tail);
    }
    return *this;
}

template <typename T>
void linear_linked_list<T>::reverse(Node* current, Node* prev)
{
    if(current->next != nullptr)
    {
        reverse(current->next, current);
    }

    current->next = prev;

    return;
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::sort()
{
    return sort([](const T& lhs, const T& rhs){ return lhs < rhs; });
}

template <typename T>
template <class Compare>
linear_linked_list<T>& linear_linked_list<T>::sort(Compare&& comp)
{
    if(head == nullptr || head->next == nullptr)
    {
        return *this;
    }

    linear_linked_list<T> right = split(middle());

    sort(comp);
    right.sort(comp);

    return merge(right, comp);
}

template <typename T>
linear_linked_list<T> linear_linked_list<T>::split(const_iterator pos)
{
    linear_linked_list<T> temp;

    if(pos.node != nullptr)
    {
        temp.head = pos.node->next;
        temp.tail = (temp.head == nullptr) ? nullptr : tail;

        tail = pos.node;
        tail->next = nullptr;
    }
    return temp;
}

template <typename T>
linear_linked_list<T>& linear_linked_list<T>::merge(self_type& list)
{
    return merge(list, [](const T& lhs, const T& rhs){ return lhs < rhs; });
}

template <typename T>
template <class Compare>
linear_linked_list<T>& linear_linked_list<T>::merge(self_type& list, Compare&& comp)
{
    if(&list != this)
    {
        head = merge(head, list.head, comp);

        // set tail to the "greater" of the two tails OR whichever tail isn't null
        tail = !tail || (list.tail && comp(tail->data, list.tail->data))
             ? list.tail : tail;

        // Merge does not copy, source must relinquish resources
        list.head = list.tail = nullptr;
    }
    return *this;
}

template <typename T>
template <class Compare>
typename linear_linked_list<T>::Node* 
linear_linked_list<T>::merge(Node* self, Node* other, Compare&& comp)
{
    // Base case : self OR other list is empty return the non-empty list
    if (self == nullptr) { return other; }
    if (other == nullptr) { return self; }

    bool comparison = comp(self->data, other->data);

    Node* head = comparison ? self : other;
    head->next = comparison ? merge(self->next, other, comp) 
                            : merge(self, other->next, comp);
    return head;
}

template <typename T>
typename linear_linked_list<T>::iterator
linear_linked_list<T>::erase_after(iterator pos)
{
    if(!empty() && pos.node != tail)
    {
        Node* temp = pos.node->next;
        pos.node->next = temp->next;
        delete temp;
    }
    return pos;
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
    return size(head);
}

template <typename T>
typename linear_linked_list<T>::size_type linear_linked_list<T>::size(Node* head) const
{
    return (head != nullptr) ? 1 + size(head->next) : 0;
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

template <typename T>
typename linear_linked_list<T>::iterator 
linear_linked_list<T>::middle()
{
    return iterator(middle(head));
}

template <typename T>
typename linear_linked_list<T>::const_iterator 
linear_linked_list<T>::middle() const
{
    return const_iterator(middle(head));
}

template <typename T>
typename linear_linked_list<T>::Node* 
linear_linked_list<T>::middle(Node* head) const
{
    if(head == nullptr || head->next == nullptr)
    {
        return head;
    }

    return middle(head, head->next);
}

template <typename T>
typename linear_linked_list<T>::Node* 
linear_linked_list<T>::middle(Node* slow, Node* fast) const
{
    return (fast == nullptr || (fast = fast->next) == nullptr) 
           ? slow : middle(slow->next, fast->next);
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
    swap(copy);

    // As the copy goes out of scope it destructs with the old data
    return *this;
}

template <typename T>
void linear_linked_list<T>::swap(self_type& origin)
{
    using std::swap;

    // Swaps pointers, reassigns ownership
    swap(head, origin.head);
    swap(tail, origin.tail);
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
#endif //LINKED_LIST_H

