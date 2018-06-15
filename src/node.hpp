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
    T* Data() const;
    Node* Next() const;

    /* Mutators */
    Node* Data(const T& value);
    Node* Next(Node* node);


private:

    T* data;
    Node* next;
};

#include "node.cpp"

#endif // NODE_H