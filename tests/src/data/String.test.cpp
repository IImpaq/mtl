/**
* @file String.test.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#include <catch2/catch_all.hpp>

#include "data/Array.hpp"
#include "data/String.hpp"

TEST_CASE("String functionality validation", "[data]") {
  using namespace ntl;

  SECTION("constructing new string") {
    REQUIRE(String{}.GetLength() == 0);
    REQUIRE(String{'a'}.GetLength() == 1);
    REQUIRE(String{"abc"}.GetLength() == 3);
  }

  SECTION("comparing") {
    String string{"abcd"};

    REQUIRE((string == String{"abcd"}) == true);
    REQUIRE((string == "abcd") == true);
    REQUIRE((string != String{"abcd"}) == false);
    REQUIRE((string != "abcd") == false);
    REQUIRE((string == String{"efg"}) == false);
    REQUIRE((string == "efg") == false);
    REQUIRE((string != String{"efg"}) == true);
    REQUIRE((string != "efg") == true);
  }

  SECTION("constructing from another string") {
    String original{"abcd"};

    REQUIRE(String{original} == String{"abcd"});
    REQUIRE(original.GetLength() == 4);
    REQUIRE(String{std::move(original)} == String{"abcd"});
    REQUIRE(original.GetLength() == 0);
  }

  SECTION("modifying content") {
    String string{"AbC"};

    REQUIRE(string.ToLowerCase() == String{"abc"});
    REQUIRE(string.ToLowerCase() == "abc");
    REQUIRE(string.ToUpperCase() == String{"ABC"});
    REQUIRE(string.ToUpperCase() == "ABC");
  }

  SECTION("appending strings") {
    String a{"ab"};
    String b{"cd"};

    REQUIRE(a + b == String{"abcd"});
    REQUIRE(a + "cd" == String{"abcd"});
    a += b;
    b += "ef";
    REQUIRE(a == String{"abcd"});
    REQUIRE(b == String{"cdef"});
    b += a;
    a += a;
    REQUIRE(b == String{"cdefabcd"});
    REQUIRE(a == String{"abcdabcd"});

    String c{""};
    for(Size i = 0; i < 2048; ++i) {
      c += "a";
    }
    REQUIRE(c.GetLength() == 2048);
    for(Size i = 0; i < 2048; ++i) {
      REQUIRE(c[i] == 'a');
    }
  }

  SECTION("accessing chars of string") {
    String string{"abcd"};

    REQUIRE(string[0] == 'a');
    REQUIRE(string[1] == 'b');
    REQUIRE(string[2] == 'c');
    REQUIRE(string[3] == 'd');
    string[1] = 'e';
    string[3] = 'f';
    REQUIRE(string[0] == 'a');
    REQUIRE(string[1] == 'e');
    REQUIRE(string[2] == 'c');
    REQUIRE(string[3] == 'f');
  }

  SECTION("replacing characters in string") {
    String string{"aabcdde"};

    REQUIRE(string.Replace('a', 'f') == "ffbcdde");
    REQUIRE(string.GetLength() == 7);
    REQUIRE(string.Replace('c', '\0') == "ffbdde");
    REQUIRE(string.GetLength() == 6);
  }

  SECTION("finding character in string") {
    String string{"aabcdde"};

    REQUIRE(string.Find('a') == 0);
    REQUIRE(string.Find('b') == 2);
    REQUIRE(string.Find('d') == 4);
    REQUIRE(string.Find('e') == 6);
    REQUIRE(string.Find('f') == -1);
  }

  SECTION("replacing parts of a string") {
    String string{"aabcddff"};
    string.Replace('b', 'c');
    REQUIRE(string == "aaccddff");
    string.Replace("accdd", "hello");
    REQUIRE(string == "ahelloff");
    string.Replace("hello", "welcome");
    REQUIRE(string == "awelcomeff");
    string.Replace("welcome", "hi");
    REQUIRE(string == "ahiff");
    string.Replace("hi", "");
    REQUIRE(string == "aff");
  }

  SECTION("use of string iterator") {
    String string{"aabcdde"};

    Size idx = 0;
    for(char c : string) {
      REQUIRE(string[idx] == c);
      idx++;
    }
    REQUIRE(idx == string.GetLength());
  }
}