/*
File: list_test.cpp

Description: Unit tests for the linear_linked_list data structure

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#include <iostream>
#include <catch.hpp>
#include "linked_list.h"

TEST_CASE("Constructing linear_linked_list objects", "[list], [constructors]")
{
    SECTION("Default construction")
    {
        linear_linked_list<int> list;

        REQUIRE(list.empty());
    }
/*    SECTION("Copy construction")
    {
        linear_linked_list<int> origin;
        origin.add_unique(1);
        origin.add_unique(3);
        origin.add_unique(2);

        linear_linked_list<int> copy(origin);

        bool assert = origin == copy;
        REQUIRE(assert);

        assert = copy.size() == 3;
        REQUIRE(assert);
    }*/
    SECTION("Range based construction on a populated array")
    {
        int nums[] = {1, 2, 3, 4, 5};

        linear_linked_list<int> list(nums, nums + 5);

        linear_linked_list<int>::const_iterator it;
        int i = 0;
        for(it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == nums[i++];
            REQUIRE(assert);
        }
    }
    SECTION("Range base construction on an empty array")
    {
        int nums[3];

        linear_linked_list<int> list(nums, nums + 3);

        linear_linked_list<int>::const_iterator it;

        int i = 0;

        for(it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == nums[i++];
            REQUIRE(assert);
        }
    }
}

TEST_CASE("Using clear to erase the list", "[list], [clear], [destructor]")
{
    SECTION("An empty list")
    {
        linear_linked_list<char> list;

        list.clear();

        REQUIRE(list.empty());
    }
/*    SECTION("A populated list")
    {
        linear_linked_list<char> list;

        list.add_unique('a');
        list.add_unique('b');
        list.add_unique('c');

        list.clear();

        REQUIRE(list.empty());
    }
*/
}

TEST_CASE("Using swap to reassign data", "[list], [swap]")
{
/*    SECTION("An empty list and a populated list")
    {
        linear_linked_list<int> old;

        old.add_unique(3);
        old.add_unique(1);
        old.add_unique(2);

        linear_linked_list<int> list;

        linear_linked_list<int>::swap(list, old);

        int i = 1;
        for (linear_linked_list<int>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == i++;
            REQUIRE(assert);
        }
    } */
    SECTION("two empty lists")
    {
        linear_linked_list<int> old;
        linear_linked_list<int> list;

        linear_linked_list<int>::swap(list, old);

        bool assert = old == list;
        REQUIRE(assert);
    }
}
/*
TEST_CASE("Using the copy-assignment operator", "[list], [operators], [copy-assignment]")
{
    SECTION("An empty list and a populated list")
    {
        linear_linked_list<int> old;

        old.add_unique(3);
        old.add_unique(1);
        old.add_unique(2);

        linear_linked_list<int> list;

        list = old;

        bool assert = old == list;
        REQUIRE(assert);
    }
    SECTION("two empty lists")
    {
        linear_linked_list<int> old;
        linear_linked_list<int> list;

        old = list;

        bool assert = old == list;
        REQUIRE(assert);
    }
}
*/
struct remove_seven
{
    bool operator() (const int& value)
    {
        return value == 7;
    }
};

TEST_CASE("Using functors to remove a specific element", "[list], [operations]")
{
    SECTION("remove_if with a value constructed functor")
    {
        remove_seven functor;

        int nums[] = { 1, 2, 3, 4, 7, 5, 6 };

        linear_linked_list<int> list(nums, nums + 7);

        REQUIRE(list.remove_if(functor));

        int i = 0;
        linear_linked_list<int>::const_iterator it;
        for (it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == ++i;
            REQUIRE(assert);
        }
    }
    SECTION("remove_if with the element as the head")
    {
        int nums[] = { 7, 1, 2, 3, 4, 5, 6 };

        linear_linked_list<int> list(nums, nums + 7);

        REQUIRE(list.remove_if(remove_seven()));

        int i = 0;
        linear_linked_list<int>::const_iterator it;
        for (it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == ++i;
            REQUIRE(assert);
        }
    }
    SECTION("remove_if with the element as the tail")
    {
        int nums[] = { 1, 2, 3, 4, 5, 6, 7 };

        linear_linked_list<int> list(nums, nums + 7);

        REQUIRE(list.remove_if(remove_seven()));

        int i = 0;
        linear_linked_list<int>::const_iterator it;
        for (it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == ++i;
            REQUIRE(assert);
        }
    }
    SECTION("remove_if with no matching element")
    {
        int nums[] = { 1, 2, 3, 4, 5, 6 };

        linear_linked_list<int> list(nums, nums + 6);

        REQUIRE(!list.remove_if(remove_seven()));
    }
}

TEST_CASE("Using mutable iterators to modify data", "[list], [iterators]")
{
    int nums[] = { 1, 2, 3, 4, 5, 6, 7 };

    linear_linked_list<int> list(nums, nums + 7);

    int i = 1;
    for (linear_linked_list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        ++(*it);
        bool assert = *it = ++i;
        REQUIRE(assert);
    }
}
