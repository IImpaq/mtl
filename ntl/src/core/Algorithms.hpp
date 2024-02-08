/**
* @file Algorithms.hpp
* @author Marcus Gugacs
* @date 02/07/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_ALGORITHMS_HPP
#define NTL_ALGORITHMS_HPP

namespace ntl::algorithms {
  enum class Sort {
    DYNAMIC = 0,
    INSERTION_SORT = 1,
    QUICK_SORT = 2,
    MERGE_SORT = 3
  };

  enum class Search {
    BINARY_SEARCH = 0,
    FRONT_BACK_SEARCH = 1
  };
}

#endif // NTL_ALGORITHMS_HPP
