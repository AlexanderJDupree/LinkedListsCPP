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

    // TODO make pop_back methods
    // Removes the element at the front of the list
    self_type& pop_front();

    // Copies the front element onto the out_param and removes it
    reference pop_front(reference out_param);

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

#include "linear_linked_list.cpp"

#endif //LINKED_LIST_H

