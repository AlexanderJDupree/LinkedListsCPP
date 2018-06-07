// Linked List implementations

#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "linkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(size_t count, const T& data) : LinkedList()
{
    while (count > 0)
    {
        push_front(data);
        --count;
    }
}

// Iterator Class
template <typename T>
LinkedList<T>::iterator::iterator(const pointer ptr) : node(ptr) {}

// Operator Overloads
template <typename T>
bool LinkedList<T>::iterator::operator==(const self_type& rhs) const
{
    return node == rhs.node;
}

template <typename T>
bool LinkedList<T>::iterator::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
typename LinkedList<T>::iterator::self_type& LinkedList<T>::iterator::operator++()
{
    node = node->Next();
    return *this;
}

template <typename T>
typename LinkedList<T>::iterator::self_type LinkedList<T>::iterator::operator++(int)
{
    iterator copy = iterator(*this);
    ++(*this);
    return copy;
}

template <typename T>
typename LinkedList<T>::iterator::reference LinkedList<T>::iterator::operator*()
{
    return *node->Data();
}
// End Iterator Class

// const_iterator Class
template <typename T>
LinkedList<T>::const_iterator::const_iterator(const pointer ptr) : node(ptr) {}

// Operator Overloads
template <typename T>
bool LinkedList<T>::const_iterator::operator==(const self_type& rhs) const
{
    return node == rhs.node;
}

template <typename T>
bool LinkedList<T>::const_iterator::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
typename LinkedList<T>::const_iterator::self_type& 
LinkedList<T>::const_iterator::operator++()
{
    node = node->Next();
    return *this;
}

template <typename T>
typename LinkedList<T>::const_iterator::self_type 
LinkedList<T>::const_iterator::operator++(int)
{
    const_iterator copy = const_iterator(*this);
    ++(*this);
    return copy;
}

template <typename T>
typename LinkedList<T>::const_iterator::reference 
LinkedList<T>::const_iterator::operator*() const
{
    return *node->Data();
}
// End const_iterator Class


// Iterators
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
    return const_iterator(tail->Next());
} 

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end()
{
    return iterator(tail->Next());
} 

// Modifiers
template <typename T>
void LinkedList<T>::push_front(const T& data)
{
    Node<T>* temp = new Node<T>(data);

    temp->Next(head);
    head = temp;

    if (tail == nullptr)
    {
        tail = head;
    }

    return;
}

template <typename T>
void LinkedList<T>::push_back(const T& data)
{
    if (this->empty())
    {
        push_front(data);
        return;
    }

    Node<T>* temp = new Node<T>(data);

    tail->Next(temp);
    tail = temp;

    return;
}

template<typename T>
void LinkedList<T>::insert(const LinkedList<T>::iterator &insertionPoint, 
                           const T& data)
{
    if (insertionPoint == begin())
    {
        push_front(data);
        return;
    }

    Node<T>* newNode = new Node<T>(data);
    Node<T>* current = head;
    Node<T>* previous;
    
    LinkedList<T>::iterator It;
    for (It = begin(); It != insertionPoint; It++)
    {
        previous = current;
        current = current->Next();
    }

    newNode->Next(previous->Next());
    previous->Next(newNode);

    return;
}

template <typename T>
void LinkedList<T>::clear()
{
    if (head == nullptr)
    {
        return;
    }

    Node<T>* previous = head;

    while (head != nullptr)
    {
        previous = head;
        head = head->Next();
        delete previous;
    }

    return;
}

// Capacity functions
template <typename T>
bool LinkedList<T>::empty() const
{
    return !(head);
}

template <typename T>
size_t LinkedList<T>::size() const
{
    size_t SIZE = 0;
    Node<T>* temp = head;
    while (temp != nullptr)
    {
        ++SIZE;
        temp = temp->Next();
    }
    return SIZE;
}

#endif // LINKED_LIST_TPP
