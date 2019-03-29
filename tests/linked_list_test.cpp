/*
 
 File: linked_list_test.cpp

 Brief: Unit tests for linear linked list data structure

 Copyright (c) 2018 Alexander DuPree

 This software is released as open source through the MIT License

 Authors: Alexander DuPree, Jacob Bickle

 https://github.com/AlexanderJDupree/LinkedListsCPP

*/


#include <vector>
#include <iostream>
#include <catch.hpp>
#include "linear_linked_list.hpp"

TEST_CASE("Constructing linear_linked_list objects", "[constructors]")
{
    SECTION("Default construction")
    {
        linear_linked_list<int> list;

        REQUIRE(list.empty());
        REQUIRE(list.size() == 0);
    }
    SECTION("Copy construction")
    {
        linear_linked_list<int> origin { 1, 2, 3, 4, 5 };
        linear_linked_list<int> copy(origin);

        REQUIRE(origin == copy);
        REQUIRE(copy.size() == 5);
    }
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
    SECTION("Ranged based construction with a standard container")
    {
        std::vector<int> nums = { 1, 2, 3, 4, 5 };

        linear_linked_list<int> list(nums.begin(), nums.end());

        std::vector<int>::iterator iter = nums.begin();
        for(auto num : list)
        {
            REQUIRE(num == *(iter++));
        }
    }
    SECTION("Initializer list construction")
    {
        linear_linked_list<int> list { 1, 2, 3, 4, 5 };
        int i = 0;
        for(auto num : list)
        {
            REQUIRE(num == ++i);
        }
    }
}

TEST_CASE("Using clear to erase the list", "[clear], [destructor]")
{
    SECTION("An empty list")
    {
        linear_linked_list<char> list;

        list.clear();

        REQUIRE(list.empty());
    }
    SECTION("A populated list")
    {
        linear_linked_list<char> list { 'a', 'b', 'c' };

        list.clear();

        REQUIRE(list.empty());
    }
}

TEST_CASE("Front/Back element access", "[front], [back]")
{
    SECTION("A populated list")
    {
        linear_linked_list<int> list {1, 2, 3, 4, 5};

        REQUIRE(list.front() == 1);
        REQUIRE(list.back() == 5);
    }
    SECTION("front and back are the same with a list with one element")
    {
        linear_linked_list<int> list { 1 };

        REQUIRE(list.front() == list.back());
    }
    SECTION("Empty list front/back access will throw a logic_error")
    {
        linear_linked_list<int> empty_list;

        REQUIRE_THROWS(empty_list.front());
        REQUIRE_THROWS(empty_list.back());
    }
}

TEST_CASE("Pushing to elements to the front of the list", "[push_front]")
{
    SECTION("An empty list")
    {
        linear_linked_list<char> list;

        REQUIRE(list.push_front('a').front() == 'a');
    }
    SECTION("A populated list")
    {
        linear_linked_list<int> list {1, 2, 3, 4, 5};

        REQUIRE(list.push_front(42).front() == 42);
    }
    SECTION("Pushing multiple elements")
    {
        linear_linked_list<int> list; 

        list.push_front(3).push_front(2).push_front(1);

        int i = 0;
        for (auto num : list)
        {
            REQUIRE(num == ++i);
        }
    }
}

TEST_CASE("Pushing to elements to the back of the list", "[push_back]")
{
    SECTION("An empty list")
    {
        linear_linked_list<char> list;

        REQUIRE(list.push_back('a').front() == 'a');
    }
    SECTION("A populated list")
    {
        linear_linked_list<int> list {1, 2, 3, 4, 5};

        REQUIRE(list.push_back(42).back() == 42);
    }
    SECTION("Pushing multiple elements")
    {
        linear_linked_list<int> list; 

        list.push_back(1).push_back(2).push_back(3);

        int i = 0;
        for (auto num : list)
        {
            REQUIRE(num == ++i);
        }
    }
}

TEST_CASE("Using swap to reassign data", "[swap]")
{
    SECTION("An empty list and a populated list")
    {
        linear_linked_list<int> old {1, 2, 3};

        linear_linked_list<int> list;

        linear_linked_list<int>::swap(list, old);

        int i = 0;
        for (const auto& elem : list)
        {
            REQUIRE(elem == ++i);
        }
        REQUIRE(old.empty());
    }
    SECTION("two empty lists")
    {
        linear_linked_list<int> old;
        linear_linked_list<int> list;

        linear_linked_list<int>::swap(list, old);

        REQUIRE(old == list);
    }
}

TEST_CASE("Using the copy-assignment operator", "[operators], [copy-assignment]")
{
    SECTION("An empty list and a populated list")
    {
        linear_linked_list<int> old { 1, 2, 3 };

        linear_linked_list<int> list;

        REQUIRE((list = old) == old);
    }
    SECTION("two empty lists")
    {
        linear_linked_list<int> old;
        linear_linked_list<int> list;

        REQUIRE((old = list) == list);
    }
}

TEST_CASE("Testing equality between lists", "[operators], [equality]")
{
    SECTION("Two empty lists")
    {
        linear_linked_list<int> lhs;
        linear_linked_list<int> rhs;

        REQUIRE(lhs == rhs);
    }
    SECTION("Two populated lists of differing sizes")
    {
         linear_linked_list<int> lhs { 1, 2, 3 };
         linear_linked_list<int> rhs { 1, 2, 3, 4 };

         REQUIRE(lhs != rhs);
    }
    SECTION("Two populated lists of matching sizes")
    {
         linear_linked_list<int> lhs { 1, 2, 3 };
         linear_linked_list<int> rhs { 1, 2, 4 };

         REQUIRE(lhs != rhs);
    }
    SECTION("Two populated lists with matching elements")
    {
         linear_linked_list<int> lhs { 1, 2, 3 };
         linear_linked_list<int> rhs { 1, 2, 3 };

         REQUIRE(lhs == rhs);
    }
}

TEST_CASE("Popping the front element off the list", "[operations], [pop_front]")
{
    SECTION("pop the front of an empty list")
    {
        linear_linked_list<int> empty_list;

        REQUIRE(empty_list.pop_front().empty());
    }
    SECTION("Pop the front of a list with one element")
    {
        linear_linked_list<int> list { 1 };

        REQUIRE(list.pop_front().empty());
    }
    SECTION("Pop the front of a populated list")
    {
        linear_linked_list<int> list { 7, 1, 2, 3 };

        list.pop_front();

        int i = 0;
        for (const auto& n : list)
        {
            REQUIRE(n == ++i);
        }
    }
    SECTION("Pop the front of an empty list with out parameter")
    {
        int i = 7;

        linear_linked_list<int> empty_list;

        REQUIRE(empty_list.pop_front(i) == 7);
    }
    SECTION("Pop the front of a populated list")
    {
        int i = 7;

        linear_linked_list<int> list { 1, 2, 3, 4 };

        REQUIRE(list.pop_front(i) == 1);
    }
}

TEST_CASE("Removing a specific element from a list", "[operations], [remove]")
{
    linear_linked_list<int> list { 1, 4, 2, 3, 4 };

    SECTION("Remove from a populated list")
    {
        REQUIRE(list.remove(4) == 2);
        REQUIRE(list.size() == 3);
    }

    SECTION("Removing an item not found in a list")
    {
        REQUIRE(list.remove(7) == 0);
    }
}

struct remove_seven
{
    bool operator() (const int& value)
    {
        return value == 7;
    }
};

TEST_CASE("Using functors to remove a specific element", "[remove_if]")
{
    SECTION("remove_if with a value constructed functor")
    {
        remove_seven functor;

        int nums[] = { 7, 1, 2, 3, 4, 7, 5, 6, 7};

        linear_linked_list<int> list(nums, nums + 9);

        REQUIRE(list.remove_if(functor) == 3);

        int i = 0;
        linear_linked_list<int>::const_iterator it;
        for (it = list.begin(); it != list.end(); ++it)
        {
            REQUIRE(*it == ++i);
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
            REQUIRE(*it == ++i);
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
            REQUIRE(*it == ++i);
        }
    }
    SECTION("remove_if with no matching element")
    {
        int nums[] = { 1, 2, 3, 4, 5, 6 };

        linear_linked_list<int> list(nums, nums + 6);

        REQUIRE(!list.remove_if(remove_seven()));
    }
    SECTION("remove_if with an empty list")
    {
        linear_linked_list<int> list;

        REQUIRE_FALSE(list.remove_if(remove_seven()));
    }
}

TEST_CASE("Using mutable iterators to modify data", "[iterators]")
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

TEST_CASE("Reversing the order of a list", "[reverse]")
{
    SECTION("Empty list")
    {
        linear_linked_list<int> empty_list;

        REQUIRE(empty_list.reverse().empty());
    }
    SECTION("A list with one element")
    {
        
        linear_linked_list<int> list { 1 };

        REQUIRE((list.reverse().front() == (list.back() == 1)));
    }
    SECTION("A populated list")
    {
        linear_linked_list<int> list { 5, 4, 3, 2, 1 };
        
        list.reverse();

        int i = 0;
        for(auto num : list)
        {
            REQUIRE(num == ++i);
        }
    }
}


