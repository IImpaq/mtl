/**
* @file List.test.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#include <catch2/catch_all.hpp>

#include "data/List.hpp"

TEST_CASE("List functionality validation", "[data]") {
  using namespace ntl;

  SECTION("constructing new list") {
    List<int> list{};

    REQUIRE(list.GetSize() == 0);
    REQUIRE(list.IsEmpty());
  }

  SECTION("constructing list from another one") {
    List<int> list{};
    list.InsertFront(2);
    list.InsertFront(4);
    list.InsertFront(8);

    List<int> list2(list);
    REQUIRE(list2.GetSize() == 3);
    REQUIRE(list2.ToString() == String{"List(8, 4, 2)\n"});
  }

  SECTION("adding elements to front of the list") {
    List<int> list{};
    list.InsertFront(2);
    list.InsertFront(4);
    list.InsertFront(8);

    REQUIRE(list.GetSize() == 3);
    REQUIRE(list.ToString() == String{"List(8, 4, 2)\n"});
  }

  SECTION("adding elements to back of the list") {
    List<int> list{};
    list.InsertBack(2);
    list.InsertBack(4);
    list.InsertBack(8);

    REQUIRE(list.GetSize() == 3);
    REQUIRE(list.ToString() == String{"List(2, 4, 8)\n"});
  }

  SECTION("adding elements after another one in the list") {
    List<int> list{};
    auto* added = list.InsertFront(2);
    list.InsertAfter(added, 4);
    auto* added2 = list.InsertBack(8);
    list.InsertAfter(added2, 16);

    REQUIRE(list.GetSize() == 4);
    REQUIRE(list.ToString() == String{"List(2, 4, 8, 16)\n"});
  }

  SECTION("checking if the list is empty") {
    List<int> list{};
    REQUIRE(list.IsEmpty());
    list.InsertBack(2);
    REQUIRE(!list.IsEmpty());
    list.Clear();
    REQUIRE(list.IsEmpty());
    list.InsertFront(2);
    REQUIRE(!list.IsEmpty());
  }

  SECTION("adding elements in the middle of to list") {
    List<int> list{};
    auto* added = list.InsertFront(2);
    list.InsertBack(8);
    list.InsertAfter(added, 4);

    REQUIRE(list.ToString() == String{"List(2, 4, 8)\n"});
    REQUIRE(list.GetSize() == 3);
  }

  SECTION("removing elements from the list") {
    List<int> list{};
    auto* added = list.InsertFront(2);
    list.InsertBack(8);
    list.InsertAfter(added, 4);

    list.RemoveElement(4);
    list.RemoveElement(2);
    list.RemoveElement(8);

    REQUIRE(list.IsEmpty());
  }

  SECTION("removing element after node from the list") {
    List<int> list{};
    auto* added = list.InsertFront(2);
    list.InsertBack(8);
    list.InsertAfter(added, 4);
    list.InsertBack(16);

    list.RemoveAfter(list.FindElement(2));
    list.RemoveAfter(list.FindElement(2));
    list.RemoveAfter(list.FindElement(2));

    REQUIRE(list.GetSize() == 1);
    REQUIRE(list.ToString() == String{"List(2)\n"});
  }

  SECTION("comparing to equal lists") {
    List<int> list1{};
    List<int> list2{};
    auto* added = list1.InsertFront(2);
    list1.InsertBack(8);
    list1.InsertAfter(added, 4);

    list2.InsertFront(4);
    list2.InsertBack(8);
    list2.InsertFront(2);

    REQUIRE(list1 == list2);
    REQUIRE(!(list2 != list1));
  }

  SECTION("comparing to unequal lists") {
    List<int> list1{};
    List<int> list2{};
    auto* added = list1.InsertFront(2);
    list1.InsertBack(8);
    list1.InsertAfter(added, 4);

    list2.InsertFront(8);
    list2.InsertBack(4);
    list2.InsertFront(2);

    REQUIRE(list1 != list2);
    REQUIRE(!(list2 == list1));
  }

  SECTION("usage of linked list iterator") {
    List<int> list{};

    list.InsertFront(4);
    list.InsertBack(8);
    list.InsertFront(2);

    Size idx = 0;
    for(auto i : list) {
      idx++;
    }
    REQUIRE(idx == 3);

    Size value = 2;
    for(auto it = list.begin(), end = list.end(); it != end; ++it) {
      const auto i = *it;
      REQUIRE(i == value);
      value *= 2;
    }
  }
}