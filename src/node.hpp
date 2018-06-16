/*

File: node.hpp

Copyright (c) 2018 Alexander DuPree

This software is released as open source through the MIT License

Authors: Alexander DuPree, Jacob Bickle

https://github.com/AlexanderJDupree/LinkedListsCPP

*/

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
    T* data() const;
    Node* next() const;

    /* Mutators */
    Node* data(const T& value);
    Node* next(Node* node);


private:

    T* _data;
    Node* _next;
};

#include "node.cpp"

#endif // NODE_H
