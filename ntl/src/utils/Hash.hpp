/**
* @file Hash.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_HASH_UTILS_HPP
#define NTL_HASH_UTILS_HPP

#include <iostream>

namespace ntl::hash {
  /**
   * @source: https://stackoverflow.com/a/57595105
   */
  template <typename T, typename... Rest>
  void Combine(std::size_t& seed, const T& v, const Rest&... rest) {
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (HashCombine(seed, rest), ...);
  };
}

#endif // NTL_HASH_UTILS_HPP
