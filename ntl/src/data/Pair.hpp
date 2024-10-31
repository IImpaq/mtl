/**
* @file Pair.hpp
 * @author Marcus Gugacs
 * @date 10/31/2024
 * @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
 */

#ifndef NTL_PAIR_HPP
#define NTL_PAIR_HPP

#include <utility>

namespace ntl {
  template <typename FirstType, typename SecondType>
  struct Pair {
    FirstType first;
    SecondType second;

    // Default constructor
    Pair() = default;

    // Parameterized constructor
    Pair(const FirstType &first, const SecondType &second)
        : first(first), second(second) {}

    // Copy constructor
    Pair(const Pair &other) : first(other.first), second(other.second) {}

    // Move constructor
    Pair(Pair &&other) noexcept
        : first(std::move(other.first)), second(std::move(other.second)) {}

    // Copy assignment operator
    Pair &operator=(const Pair &other) {
      if (this != &other) {
        first = other.first;
        second = other.second;
      }
      return *this;
    }

    // Move assignment operator
    Pair &operator=(Pair &&other) noexcept {
      if (this != &other) {
        first = std::move(other.first);
        second = std::move(other.second);
      }
      return *this;
    }

    // Equality operator
    bool operator==(const Pair &other) const {
      return first == other.first && second == other.second;
    }

    // Inequality operator
    bool operator!=(const Pair &other) const { return !(*this == other); }
  };
} // namespace ntl

#endif // NTL_PAIR_HPP
