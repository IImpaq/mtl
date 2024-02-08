/**
* @file Stack.test.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#include <catch2/catch_all.hpp>

#include "data/Stack.hpp"

TEST_CASE("Stack functionality validation", "[data]") {
  using namespace ntl;

  SECTION("constructing new stack") {
    Stack<int> stack{};
    REQUIRE(stack.GetSize() == 0);
  }

  SECTION("push an element onto the stack") {
    Stack<int> stack{};
    stack.Push(2);
    REQUIRE(stack.GetSize() == 1);
    stack.Push(4);
    REQUIRE(stack.GetSize() == 2);
    stack.Push(8);
    REQUIRE(stack.GetSize() == 3);
  }

  SECTION("popping an element from the stack") {
    Stack<int> stack{};
    stack.Push(2);
    stack.Push(4);
    stack.Push(8);
    REQUIRE(stack.GetSize() == 3);
    REQUIRE(stack.Pop() == 8);
    REQUIRE(stack.GetSize() == 2);
    REQUIRE(stack.Pop() == 4);
    REQUIRE(stack.GetSize() == 1);
    REQUIRE(stack.Pop() == 2);
    REQUIRE(stack.GetSize() == 0);
  }

  SECTION("peeking an element from the stack") {
    Stack<int> stack{};
    stack.Push(2);
    stack.Push(4);
    stack.Push(8);
    REQUIRE(stack.GetSize() == 3);
    REQUIRE(stack.Peek() == 8);
    REQUIRE(stack.GetSize() == 3);
    stack.Pop();
    REQUIRE(stack.Peek() == 4);
    REQUIRE(stack.GetSize() == 2);
    stack.Pop();
    REQUIRE(stack.Peek() == 2);
    REQUIRE(stack.GetSize() == 1);
  }
}