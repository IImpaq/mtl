/**
* @file String.test.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#include <catch2/catch_all.hpp>

#include "data/Array.hpp"

TEST_CASE("Array functionality validation", "[data]") {
  using namespace ntl;

  SECTION("constructing new array") {
    Array<int> array(1024);

    REQUIRE(array.GetCapacity() == 1024);
    REQUIRE(array.GetSize() == 0);
  }

  SECTION("constructing array from another one") {
    Array<int> array(1024);
    array.Insert(2);
    array.Insert(4);
    array.Insert(8);

    Array<int> array2(array);
    REQUIRE(array2.GetCapacity() == 6);
    REQUIRE(array2.GetSize() == 3);
    REQUIRE(array2.Get(0) == 2);
    REQUIRE(array2.Get(1) == 4);
    REQUIRE(array2.Get(2) == 8);
  }

  SECTION("constructing array with new capacity from another one") {
    Array<int> array(1024);
    array.Insert(2);
    array.Insert(4);
    array.Insert(8);

    Array<int> array2(array, 2048);
    REQUIRE(array2.GetCapacity() == 2048);
    REQUIRE(array2.GetSize() == 3);
    REQUIRE(array2.Get(0) == 2);
    REQUIRE(array2.Get(1) == 4);
    REQUIRE(array2.Get(2) == 8);
  }

  SECTION("adding elements to array") {
    Array<int> array(2, false);
    array.Insert(8);
    REQUIRE(array.GetCapacity() == 2);
    REQUIRE(array.GetSize() == 1);

    array.Insert(16);
    REQUIRE(array.GetCapacity() == 2);
    REQUIRE(array.GetSize() == 2);
  }

  SECTION("checking if the array is empty") {
    Array<int> array(1);
    REQUIRE(array.IsEmpty());
    array.Insert(2);
    REQUIRE(!array.IsEmpty());
  }

  SECTION("adding elements at index to array") {
    Array<int> array(2, false);
    array.Insert(8, 0);
    REQUIRE(array.GetCapacity() == 2);
    REQUIRE(array.GetSize() == 1);

    array.Insert(16, 1);
    REQUIRE(array.GetCapacity() == 2);
    REQUIRE(array.GetSize() == 2);
  }

  SECTION("adding elements in the middle of to array") {
    Array<int> array(4, false);

    array.Insert(0);
    array.Insert(3);

    array.Insert(2, 1);
    array.Insert(1, 2);

    REQUIRE(array.GetCapacity() == 4);
    REQUIRE(array.GetSize() == 4);

    REQUIRE(array.Get(0) == 0);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 1);
    REQUIRE(array.Get(3) == 3);

    REQUIRE(array[0] == 0);
    REQUIRE(array[1] == 2);
    REQUIRE(array[2] == 1);
    REQUIRE(array[3] == 3);
  }

  SECTION("removing element index from array") {
    Array<float> array(3, false);
    array.Insert(8.8);
    array.Insert(16.16);
    array.Insert(32.32);

    array.Remove(2);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 2);

    array.Remove(1);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 1);

    array.Remove(0);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 0);
  }

  SECTION("removing element in reverse from array") {
    Array<float> array(3, false);
    array.Insert(8.8);
    array.Insert(16.16);
    array.Insert(32.32);

    array.Remove(0);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 2);

    array.Remove(1);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 1);

    array.Remove(0);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 0);
  }

  SECTION("removing element from array") {
    Array<int> array(3, false);
    array.Insert(8);
    array.Insert(16);
    array.Insert(32);

    array.RemoveElement(32);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 2);
    REQUIRE(array.Get(0) == 8);
    REQUIRE(array.Get(1) == 16);

    array.RemoveElement(16);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 1);
    REQUIRE(array.Get(0) == 8);

    array.RemoveElement(8);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 0);
  }

  SECTION("removing element in reverse from array") {
    Array<int> array(3, false);
    array.Insert(8);
    array.Insert(16);
    array.Insert(32);

    array.RemoveElement(8);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 2);
    REQUIRE(array.Get(0) == 16);
    REQUIRE(array.Get(1) == 32);

    array.RemoveElement(16);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 1);
    REQUIRE(array.Get(0) == 32);

    array.RemoveElement(32);
    REQUIRE(array.GetCapacity() == 3);
    REQUIRE(array.GetSize() == 0);
  }

  SECTION("adding and removing elements to array using operators") {
    Array<int> array(2, false);
    array += 8;
    REQUIRE(array.GetCapacity() == 2);
    REQUIRE(array.GetSize() == 1);

    array -= 8;
    REQUIRE(array.GetCapacity() == 2);
    REQUIRE(array.GetSize() == 0);
  }

  SECTION("swapping two elements in the array") {
    Array<int> array(3, false);
    array.Insert(8);
    array.Insert(16);
    array.Insert(32);

    array.Swap(0, 2);
    REQUIRE(array.Get(0) == 32);
    REQUIRE(array.Get(1) == 16);
    REQUIRE(array.Get(2) == 8);
    REQUIRE(array[0] == 32);
    REQUIRE(array[1] == 16);
    REQUIRE(array[2] == 8);

    array.Swap(1, 2);
    REQUIRE(array.Get(0) == 32);
    REQUIRE(array.Get(1) == 8);
    REQUIRE(array.Get(2) == 16);
    REQUIRE(array[0] == 32);
    REQUIRE(array[1] == 8);
    REQUIRE(array[2] == 16);

    array.Swap(1, 0);
    REQUIRE(array.Get(0) == 8);
    REQUIRE(array.Get(1) == 32);
    REQUIRE(array.Get(2) == 16);
    REQUIRE(array[0] == 8);
    REQUIRE(array[1] == 32);
    REQUIRE(array[2] == 16);

    array.Swap(2, 1);
    REQUIRE(array.Get(0) == 8);
    REQUIRE(array.Get(1) == 16);
    REQUIRE(array.Get(2) == 32);
    REQUIRE(array[0] == 8);
    REQUIRE(array[1] == 16);
    REQUIRE(array[2] == 32);
  }

  SECTION("resizing the array") {
    Array<int> array(3);
    array.Insert(8);
    array.Insert(16);
    array.Insert(32);

    array.Resize(6);

    REQUIRE(array.GetSize() == 3);
    REQUIRE(array.GetCapacity() == 6);
    REQUIRE(array.Get(0) == 8);
    REQUIRE(array.Get(1) == 16);
    REQUIRE(array.Get(2) == 32);
  }

  SECTION("clearing all elements in the array") {
    Array<int> array(3);
    array.Insert(8);
    array.Insert(16);
    array.Insert(32);

    array.Clear();

    REQUIRE(array.GetSize() == 0);
    REQUIRE(array.GetCapacity() == 3);
  }

  SECTION("clearing and resizing all elements in the array") {
    Array<int> array(3);
    array.Insert(8);
    array.Insert(16);
    array.Insert(32);

    array.Clear(6);

    REQUIRE(array.GetSize() == 0);
    REQUIRE(array.GetCapacity() == 6);
  }

  SECTION("finding elements in the unsorted array") {
    Array<float> array(4, false);

    REQUIRE(array.Find(64.64) == -1);

    array.Insert(64.64);
    REQUIRE(array.Find(64.64) == 0);

    array.Insert(8.8);
    array.Insert(16.16);

    REQUIRE(array.Find(16.16) == 2);
    REQUIRE(array.Find(8.8) == 1);

    array.Insert(8.8);
    REQUIRE(array.Find(8.8) == 3);
  }

  SECTION("finding elements in the automatically sorted array") {
    Array<float> array(4, true);

    REQUIRE(array.Find(64.64) == -1);

    array.Insert(64.64);
    REQUIRE(array.Find(64.64) == 0);

    array.Insert(8.8);
    array.Insert(16.16);

    REQUIRE(array.Find(16.16) == 1);
    REQUIRE(array.Find(8.8) == 0);

    array.Insert(8.8);
    REQUIRE(array.Find(8.8) == 1);
  }

  SECTION("sorting elements in the array using insertion sort") {
    Array<float> array(8, false);

    array.Insert(4);
    array.Insert(2);
    array.Insert(8);
    array.Insert(6);
    array.Insert(-1);
    array.Insert(0);
    array.Insert(-4);
    array.Insert(6);

    REQUIRE(array.Get(0) == 4);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 8);
    REQUIRE(array.Get(3) == 6);
    REQUIRE(array.Get(4) == -1);
    REQUIRE(array.Get(5) == 0);
    REQUIRE(array.Get(6) == -4);
    REQUIRE(array.Get(7) == 6);

    array.Sort(algorithms::Sort::INSERTION_SORT);

    REQUIRE(array.Get(0) == -4);
    REQUIRE(array.Get(1) == -1);
    REQUIRE(array.Get(2) == 0);
    REQUIRE(array.Get(3) == 2);
    REQUIRE(array.Get(4) == 4);
    REQUIRE(array.Get(5) == 6);
    REQUIRE(array.Get(6) == 6);
    REQUIRE(array.Get(7) == 8);
  }

  SECTION("sorting elements in the array using quick sort") {
    Array<float> array(8, false);

    array.Insert(4);
    array.Insert(2);
    array.Insert(8);
    array.Insert(6);
    array.Insert(-1);
    array.Insert(0);
    array.Insert(-4);
    array.Insert(6);

    REQUIRE(array.Get(0) == 4);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 8);
    REQUIRE(array.Get(3) == 6);
    REQUIRE(array.Get(4) == -1);
    REQUIRE(array.Get(5) == 0);
    REQUIRE(array.Get(6) == -4);
    REQUIRE(array.Get(7) == 6);

    array.Sort(algorithms::Sort::QUICK_SORT);

    REQUIRE(array.Get(0) == -4);
    REQUIRE(array.Get(1) == -1);
    REQUIRE(array.Get(2) == 0);
    REQUIRE(array.Get(3) == 2);
    REQUIRE(array.Get(4) == 4);
    REQUIRE(array.Get(5) == 6);
    REQUIRE(array.Get(6) == 6);
    REQUIRE(array.Get(7) == 8);
  }

  SECTION("sorting elements in the array using merge sort") {
    Array<float> array(8, false);

    array.Insert(4);
    array.Insert(2);
    array.Insert(8);
    array.Insert(6);
    array.Insert(-1);
    array.Insert(0);
    array.Insert(-4);
    array.Insert(6);

    REQUIRE(array.Get(0) == 4);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 8);
    REQUIRE(array.Get(3) == 6);
    REQUIRE(array.Get(4) == -1);
    REQUIRE(array.Get(5) == 0);
    REQUIRE(array.Get(6) == -4);
    REQUIRE(array.Get(7) == 6);

    array.Sort(algorithms::Sort::MERGE_SORT);

    REQUIRE(array.Get(0) == -4);
    REQUIRE(array.Get(1) == -1);
    REQUIRE(array.Get(2) == 0);
    REQUIRE(array.Get(3) == 2);
    REQUIRE(array.Get(4) == 4);
    REQUIRE(array.Get(5) == 6);
    REQUIRE(array.Get(6) == 6);
    REQUIRE(array.Get(7) == 8);
  }

  SECTION("sorting elements in the array using dynamic sorting") {
    Array<float> array(8, false);

    array.Insert(4);
    array.Insert(2);
    array.Insert(8);
    array.Insert(6);
    array.Insert(-1);
    array.Insert(0);
    array.Insert(-4);
    array.Insert(6);

    REQUIRE(array.Get(0) == 4);
    REQUIRE(array.Get(1) == 2);
    REQUIRE(array.Get(2) == 8);
    REQUIRE(array.Get(3) == 6);
    REQUIRE(array.Get(4) == -1);
    REQUIRE(array.Get(5) == 0);
    REQUIRE(array.Get(6) == -4);
    REQUIRE(array.Get(7) == 6);

    array.Sort(algorithms::Sort::DYNAMIC);

    REQUIRE(array.Get(0) == -4);
    REQUIRE(array.Get(1) == -1);
    REQUIRE(array.Get(2) == 0);
    REQUIRE(array.Get(3) == 2);
    REQUIRE(array.Get(4) == 4);
    REQUIRE(array.Get(5) == 6);
    REQUIRE(array.Get(6) == 6);
    REQUIRE(array.Get(7) == 8);

    array.Clear(128);
  }

  SECTION("automatically resizing the array when inserting") {
    Array<int> array(1, true, true);

    REQUIRE(array.GetCapacity() == 1);
    REQUIRE(array.GetSize() == 0);

    array.Insert(0);
    REQUIRE(array.GetCapacity() == 1);
    REQUIRE(array.GetSize() == 1);

    array.Insert(1);
    REQUIRE(array.GetCapacity() == 2);
    REQUIRE(array.GetSize() == 2);
  }

  SECTION("getting a subarray from the array") {
    Array<int> array(5);
    array.Insert(8);
    array.Insert(16);
    array.Insert(32);
    array.Insert(48);
    array.Insert(64);

    auto other = array.GetSubArray(1, 3);
    REQUIRE(other.GetCapacity() == 2);
    REQUIRE(other.GetSize() == 2);
    REQUIRE(other.Get(0) == 16);
    REQUIRE(other.Get(1) == 32);
  }

  SECTION("comparing two arrays") {
    Array<int> array1(3);
    Array<int> array2(3);

    array1.Insert(8);
    array1.Insert(16);

    array2.Insert(8);
    array2.Insert(16);

    REQUIRE(array1.IsEqual(array2));
    REQUIRE(array1 == array2);
    REQUIRE(!(array1 != array2));
  }

  SECTION("comparing two auto sorted arrays") {
    Array<int> array1(3, true);
    Array<int> array2(3, true);

    array1.Insert(8);
    array1.Insert(16);

    array2.Insert(16);
    array2.Insert(8);

    REQUIRE(array1.IsEqual(array2));
    REQUIRE(array1 == array2);
    REQUIRE(!(array1 != array2));
  }

  SECTION("comparing two different arrays") {
    Array<int> array1(3, false);
    Array<int> array2(3, false);

    array1.Insert(8);
    array1.Insert(16);

    array2.Insert(16);
    array2.Insert(8);

    REQUIRE(!array1.IsEqual(array2));
    REQUIRE(!(array1 == array2));
    REQUIRE(array1 != array2);
  }

  SECTION("creating string out of array") {
    Array<int> array(3);

    array.Insert(8);
    array.Insert(16);
    array.Insert(32);

    REQUIRE(array.ToString() == String{"Array(8, 16, 32)\n"});
  }

  SECTION("creating an array containing custom objects") {
    class Test {
    public:
      Test() {}
    };

    Array<Test> array(3, false);

    array.Insert({});
    array.Insert({});
  }

  SECTION("usage of array iterator") {
    Array<int> array(3, false);

    array.Insert(4);
    array.Insert(2);
    array.Insert(8);

    Size idx = 0;
    for (auto i : array) {
      idx++;
    }
    REQUIRE(idx == 3);

    idx = 0;
    for (auto it = array.begin(), end = array.end(); it != end; ++it) {
      const auto i = *it;
      REQUIRE(i == array[idx]);
      idx++;
    }
    REQUIRE(idx == 3);
  }
}
