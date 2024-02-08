/**
* @file Bitset.test.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#include <catch2/catch_all.hpp>

#include "data/Bitset.hpp"

TEST_CASE("Bitset functionality validation", "[data]") {
  using namespace ntl;

  SECTION("constructing new bitset") {
    Bitset bitset{};
    REQUIRE(bitset.GetSize() == 1024);
    REQUIRE(bitset.GetCapacity() == 1025);
  }

  SECTION("setting bits of the bitset") {
    Bitset<4> bitset{};
    REQUIRE(bitset.GetSize() == 4);

    bitset.Set(2);
    REQUIRE(!bitset.IsSet(0));
    REQUIRE(!bitset.IsSet(1));
    REQUIRE(bitset.IsSet(2));
    REQUIRE(!bitset.IsSet(3));

    bitset.Set(0);
    REQUIRE(bitset.IsSet(0));
    REQUIRE(!bitset.IsSet(1));
    REQUIRE(bitset.IsSet(2));
    REQUIRE(!bitset.IsSet(3));
  }

  SECTION("resetting a bit of the bitset") {
    Bitset<4> bitset{};

    bitset.Set(2);
    REQUIRE(bitset.IsSet(2));

    bitset.Reset(2);
    REQUIRE(!bitset.IsSet(2));
  }

  SECTION("resetting all bits of the bitset") {
    Bitset<4> bitset{};

    bitset.Set(2);
    REQUIRE(!bitset.IsSet(0));
    REQUIRE(!bitset.IsSet(1));
    REQUIRE(bitset.IsSet(2));
    REQUIRE(!bitset.IsSet(3));

    bitset.Set(0);
    REQUIRE(bitset.IsSet(0));
    REQUIRE(!bitset.IsSet(1));
    REQUIRE(bitset.IsSet(2));
    REQUIRE(!bitset.IsSet(3));

    bitset.Reset();
    REQUIRE(!bitset.IsSet(0));
    REQUIRE(!bitset.IsSet(1));
    REQUIRE(!bitset.IsSet(2));
    REQUIRE(!bitset.IsSet(3));
  }

  SECTION("flipping bits from the bitset") {
    Bitset<4> bitset{};

    bitset.Flip(2);
    REQUIRE(bitset.IsSet(2));

    bitset.Flip(2);
    REQUIRE(!bitset.IsSet(2));
  }

  SECTION("getting bit from the bitset") {
    Bitset<4> bitset{};

    bitset.Flip(2);
    REQUIRE(bitset.Get(2) == '1');

    bitset.Flip(2);
    REQUIRE(bitset.Get(2) == '0');
  }

  SECTION("getting count of set bits from the bitset") {
    Bitset<4> bitset{};

    bitset.Flip(2);
    REQUIRE(bitset.GetCount() == 1);
  }

  SECTION("getting if any bit in bitset is set") {
    Bitset<4> bitset{};

    REQUIRE(!bitset.IsAny());
    bitset.Flip(2);
    REQUIRE(bitset.IsAny());
  }

  SECTION("getting if no bit in bitset is set") {
    Bitset<4> bitset{};

    REQUIRE(bitset.IsNone());
    bitset.Flip(2);
    REQUIRE(!bitset.IsNone());
  }

  SECTION("converting bitset to string") {
    Bitset<4> bitset{};

    bitset.Flip(2);
    REQUIRE(bitset.ToString() == String{"Bitset(0010)\n"});
  }

  SECTION("comparing two bitsets") {
    Bitset<4> bitset1{};
    Bitset<4> bitset2{};
    REQUIRE(bitset1 == bitset2);
    REQUIRE(!(bitset1 != bitset2));

    bitset1.Flip(2);
    REQUIRE(!(bitset1 == bitset2));
    REQUIRE(bitset1 != bitset2);

    bitset2.Flip(2);
    REQUIRE(bitset1 == bitset2);
    REQUIRE(!(bitset1 != bitset2));
  }
}