/*******************************************************************************
* File: linkedListTest.cpp
*
* Description: Driver runs all unit tests for our linkedList class 
*
* Author: Alexander DuPree
* 
* Compiler: GNU GCC 5.4.0
*
*******************************************************************************/

#include "catch.hpp"
#include "node.hpp"

TEST_CASE("Constructing Nodes", "[node], [constructors]")
{
    SECTION("Default Construction")
    {
        Node<int> node;

        REQUIRE(node.Data() == nullptr);
        REQUIRE(node.Next() == nullptr);
    }
}