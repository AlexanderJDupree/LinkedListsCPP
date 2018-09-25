/*File: linked_list.h

Description: linear_linked_list is a data structure that stores data onto a node
             as well as the address for the next element in the container.

             This implementation for the linear linked list is a fully templated
             class. This allows the linear_linked_list to be instantiated to 
             store any data types. 

             By default the linear linked list COPIES the data onto the node. 
             This requires that the data object have a copy constructor defined
             or can be shallow copied with the default copy constructor.

             To access data or traverse the list, this linear linked list makes 
             use of forward iterators. The forward iterator cannot be decremented.
             The end iterator represents the element one-past the end of the
             list which is a null pointer. dereferencing end iterators causes 
             undifined behavior.

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 06/27/2018
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef> // NULL
#include <algorithm> // std::swap
#include <stdexcept> // std::logic_error

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

    // Instantiates an EMPTY list
    linear_linked_list();

    // Ranged based constructor
    template <class InputIterator>
    linear_linked_list(InputIterator begin, InputIterator end);

    // Copies each element in the original list onto this list
    linear_linked_list(const self_type& origin);
   
    // Uses clear() to delete each element in the list
    ~linear_linked_list();
     
    /****** MODIFIERS ******/

    // Adds an element to the front of the list
    self_type& push_front(const_reference data);

    // Adds an element to the back of the list
    self_type& push_back(const_reference data);

    // Removes the element at the front of the list
    self_type& pop_front();

    reference pop_front(reference out_param);

    // wrapper method for clear_list, if the list is empty does nothing
    void clear();

    // Removes the first item fullfilling the predicate functor
    template <class Predicate>
    bool remove_if(Predicate pred);

    /****** CAPACITY ******/

    // returns true if the list is empty
    bool empty() const;

    // returns the number of elements in the list
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

    /****** COMPARISON OPERATORS ******/

    // Compares sizes, then comapres each element of the list for equality
    bool operator==(const self_type& rhs) const;

    // returns the logical NOT of the equality comparison
    bool operator!=(const self_type& rhs) const;

    /****** COPY-ASSIGNMENT AND SWAP ******/

    // creates a copy of the origin, then swaps ownership with the copy
    self_type& operator=(const self_type& origin);

    // Swaps pointers to each other's resources. effectively reassigning 
    // ownership.
    static void swap(self_type& new_list, self_type& old_list);

  private:
    
    /* 
    @struct: Node

    @brief: Node is the atomic member for the linked list class. It stores
            the desired data and contains a pointer to the next node in the list.
    */
    struct Node
    {
        // Default values are default constrution and NULL
        Node(const_reference value = value_type(), Node* next = NULL) 
            : data(value), next(next) {}

        value_type data;
        Node* next;

    };

    Node* head;
    Node* tail;

    size_type _size; // Keeps track of the number of elements in the list

    /* Private Functions */

    void clear_list(Node*& current);

    template <class Predicate>
    bool remove_if(Predicate pred, Node* current);

    // Throws a logic error exception if the node* is NULL
    void throw_if_null(Node* node) const;

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

        // default constructor points the iterator to NULL
        const_forward_iterator(Node* ptr = NULL) : node(ptr) {}

        /* Operator Overloads */

        self_type& operator++(); // Prefix ++
        self_type& operator++(int); // Postfix ++

        const_reference operator*() const;
        const_pointer operator->() const;

        // returns true if each iterator is pointing to the same address in
        // memory
        bool operator==(const self_type& rhs) const;
        bool operator!=(const self_type& rhs) const;
      
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

        forward_iterator(Node* ptr = NULL) : const_forward_iterator(ptr) {}

        reference operator*();

        pointer operator->();

    };
};

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
#endif //LINKED_LIST_H

