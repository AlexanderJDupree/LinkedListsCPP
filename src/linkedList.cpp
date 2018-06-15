// Linked List implementations

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

    split(left, right);

    left = begin;

    merge_sort(left, compare);
    merge_sort(right, compare);

    begin = merge(left, right, compare);

    return;
}

template <typename T>
void LinkedList<T>::split(node_pointer& left, node_pointer& right)
{
    while((right = right->Next()) != nullptr)
    {
        if (right->Next() != nullptr)
        {
            left = left->Next();
            right = right->Next();
        }
    }
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
