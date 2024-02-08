/**
* @file Queue.test.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#include <catch2/catch_all.hpp>

#include "data/Queue.hpp"

TEST_CASE("Queue functionality validation", "[data]") {
  using namespace ntl;

  SECTION("constructing new stack") {
    Queue<int> stack{};
    REQUIRE(stack.GetSize() == 0);
  }

  SECTION("push an element onto the stack") {
    Queue<int> stack{};
    stack.Put(2);
    REQUIRE(stack.GetSize() == 1);
    stack.Put(4);
    REQUIRE(stack.GetSize() == 2);
    stack.Put(8);
    REQUIRE(stack.GetSize() == 3);
  }

  SECTION("popping an element from the stack") {
    Queue<int> stack{};
    stack.Put(2);
    stack.Put(4);
    stack.Put(8);
    REQUIRE(stack.GetSize() == 3);
    REQUIRE(stack.Get() == 2);
    REQUIRE(stack.GetSize() == 2);
    REQUIRE(stack.Get() == 4);
    REQUIRE(stack.GetSize() == 1);
    REQUIRE(stack.Get() == 8);
    REQUIRE(stack.GetSize() == 0);
  }

  SECTION("peeking an element from the stack") {
    Queue<int> stack{};
    stack.Put(2);
    stack.Put(4);
    stack.Put(8);
    REQUIRE(stack.GetSize() == 3);
    REQUIRE(stack.Peek() == 2);
    REQUIRE(stack.GetSize() == 3);
    stack.Get();
    REQUIRE(stack.Peek() == 4);
    REQUIRE(stack.GetSize() == 2);
    stack.Get();
    REQUIRE(stack.Peek() == 8);
    REQUIRE(stack.GetSize() == 1);
  }
}