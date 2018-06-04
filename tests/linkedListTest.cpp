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
#include "linkedList.hpp"

TEST_CASE("Constructing Nodes", "[node], [constructors]")
{
    SECTION("Default Construction")
    {
        Node<int> node;

        REQUIRE(*node.Data() == int());
        REQUIRE(node.Next() == nullptr);
    }
    SECTION("Overloaded Construction")
    {
        Node<char> node('n');

        REQUIRE(*node.Data() == 'n');
        REQUIRE(node.Next() == nullptr);
    }
    SECTION("Copy construction")
    {
        Node<int> node1(5);
        Node<int> node2(node1);

        REQUIRE(*node2.Data() == 5);
        REQUIRE(node2.Next() == nullptr);
    }
    
}

TEST_CASE("Using Mutators to manipulate members", "[node], [mutators]")
{
    SECTION("Manipulate data member")
    {
        Node<float> node1;
        Node<char>  node2;
        Node<int>   node3;

        node1.Data(3.545);
        node2.Data('A');
        node3.Data(77);

        REQUIRE(*node1.Data() == float(3.545));
        REQUIRE(*node2.Data() == 'A');
        REQUIRE(*node3.Data() == 77);
    }
    SECTION("Manipulate next Node member")
    {
        Node<int> node1;
        Node<int> node2;

        node1.Next(&node2);

        REQUIRE(node1.Next() == &node2);
    }
}

TEST_CASE("Link Nodes and access linked data members", "[node], [linked]")
{
    SECTION("Traverse a link to acces a different Nodes data")
    {
        Node<int> node1(1);
        Node<int> node2(7);

        node1.Next(&node2);

        REQUIRE(*node1.Next()->Data() == 7);
    }
}

TEST_CASE("Constructing Linked Lists instances", "[linkedLists], [constructors]")
{
    SECTION("Default Construction")
    {
        LinkedList<int> list;

    }
}