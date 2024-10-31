/**
* @file Map.test.cpp
* @author Marcus Gugacs
* @date 10/31/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#include <catch2/catch_all.hpp>

#include "data/Map.hpp"

TEST_CASE("Map functionality validation", "[datatypes]") {
  using namespace ntl;

  SECTION("String Key: Insert and Retrieve") {
    Map<String, int> map(10);
    map.Insert("Key1", 100);
    map.Insert("Key2", 200);
    map.Insert("Key3", 300);

    REQUIRE(map.Get("Key1") == 100);
    REQUIRE(map.Get("Key2") == 200);
    REQUIRE(map.Get("Key3") == 300);
  }

  SECTION("String Key: Remove") {
    Map<String, int> map(10);
    map.Insert("Key1", 100);
    map.Remove("Key1");

    REQUIRE(map.Exists("Key1") == false);
  }

  SECTION("String Key: Resize") {
    Map<String, int> map(2);
    for (int i = 0; i < 100; ++i) {
      map.Insert(String("Key").Append(i), i);
    }
    for (int i = 0; i < 100; ++i) {
      REQUIRE(map.Get(String("Key").Append(i)) == i);
    }
  }

  SECTION("String Key: ToString") {
    Map<String, int> map(10);

    map.Insert("Key1", 100);
    map.Insert("Key2", 200);

    auto result = map.ToString();
    REQUIRE(result == "Map(Key1 : 100, Key2 : 200)");
  }

  SECTION("String Key: Duplicate Insert") {
    Map<String, int> map(10);
    map.Insert("Key1", 100);
    map.Insert("Key1", 200);
    REQUIRE(map.Get("Key1") == 200);
  }

  SECTION("String Key: Iterating over an empty map") {
    Map<String, int> testMap(10);
    REQUIRE(testMap.GetSize() == 0);
    auto begin = testMap.begin();
    auto end = testMap.end();
    REQUIRE(begin == end);
  }

  SECTION("String Key: Iterating over a non-empty map") {
    Map<String, int> testMap(10);
    testMap.Insert("One", 1);
    testMap.Insert("Two", 2);
    testMap.Insert("Three", 3);

    REQUIRE(testMap.GetSize() == 3);

    auto begin = testMap.begin();
    auto end = testMap.end();

    REQUIRE(begin != end);
    REQUIRE(++begin != end);
    REQUIRE(++begin != end);
  }

  SECTION("String Key: Iterating through all elements") {
    Map<String, int> testMap(10);
    int counter = 0;
    for(auto it = testMap.begin(); it != testMap.end(); ++it) {
      counter++;
    }
    REQUIRE(counter == testMap.GetSize());
  }

  SECTION("Integral Key: Insert and Retrieve") {
    Map<int, int> map(10);
    map.Insert(1, 100);
    map.Insert(2, 200);
    map.Insert(3, 300);

    REQUIRE(map.Get(1) == 100);
    REQUIRE(map.Get(2) == 200);
    REQUIRE(map.Get(3) == 300);
  }

  SECTION("Integral Key: Remove") {
    Map<int, int> map(10);
    map.Insert(1, 100);
    map.Remove(1);

    REQUIRE(map.Exists(1) == false);
  }

  SECTION("Integral Key: Resize") {
    Map<int, int> map(2);
    for (int i = 0; i < 100; ++i) {
      map.Insert(i, i);
    }
    for (int i = 0; i < 100; ++i) {
      REQUIRE(map.Get(i) == i);
    }
  }

  SECTION("Integral Key: ToString") {
    Map<int, int> map(10);

    map.Insert(1, 100);
    map.Insert(2, 200);

    auto result = map.ToString();
    REQUIRE(result == "Map(1 : 100, 2 : 200)");
  }

  SECTION("Integral Key: Duplicate Insert") {
    Map<int, int> map(10);
    map.Insert(1, 100);
    map.Insert(1, 200);
    REQUIRE(map.Get(1) == 200);
  }

  SECTION("Integral Key: Iterating over an empty map") {
    Map<int, int> testMap(10);
    REQUIRE(testMap.GetSize() == 0);
    auto begin = testMap.begin();
    auto end = testMap.end();
    REQUIRE(begin == end);
  }

  SECTION("Integral Key: Iterating over a non-empty map") {
    Map<int, int> testMap(10);
    testMap.Insert(1, 1);
    testMap.Insert(2, 2);
    testMap.Insert(3, 3);

    REQUIRE(testMap.GetSize() == 3);

    auto begin = testMap.begin();
    auto end = testMap.end();

    REQUIRE(begin != end);
    REQUIRE(begin->second == 1);

    REQUIRE(++begin != end);
    REQUIRE(begin->second == 2);

    REQUIRE(++begin != end);
    REQUIRE(begin->second == 3);
  }

  SECTION("Integral Key: Iterating through all elements") {
    Map<int, int> testMap(10);
    int counter = 0;
    for(auto it = testMap.begin(); it != testMap.end(); ++it) {
      counter++;
    }
    REQUIRE(counter == testMap.GetSize());
  }
}