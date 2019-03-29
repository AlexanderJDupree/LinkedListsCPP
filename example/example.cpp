/*
 
 File: linear_linked_list.h

 Brief: Example program demonstrating basic use of a linked list
 
 Copyright (c) 2018 Alexander DuPree

 This software is released as open source through the MIT License

 Authors: Alexander DuPree

 https://github.com/AlexanderJDupree/LinkedListsCPP

*/

#include <iostream>
#include "linear_linked_list.hpp"

int main()
{
    linear_linked_list<char> list { 'H', 'E', 'L', 'L', 'O', '!', '\n' };

    for(const char& letter : list)
    {
        std::cout << letter;
    }

    // Prints "HELLO!" to the console
    
    return 0;
}


