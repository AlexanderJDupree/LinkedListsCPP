/*******************************************************************************
* File: node.h
*
* Description: 
*
* Author: Alexander DuPree
* 
* Compiler: GNU GCC 5.4.0
*
* Date: 2018 - 05 - 31
*******************************************************************************/

#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
public:

    Node();
    Node(const Node& origin);
    explicit Node(const T& value);
    ~Node();

    // Inspectors
    T* Data() const;
    Node* Next() const;

    // Mutators
    Node* Data(const T& value);
    Node* Next(Node* node);


private:

    T* data;
    Node* next;
};

#include "node.cpp"

#endif // NODE_H