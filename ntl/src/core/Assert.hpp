/**
* @file Assert.hpp
* @author Marcus Gugacs
* @date 02/07/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_ASSERT_HPP
#define NTL_ASSERT_HPP

#include <iostream>

#include "core/Platform.hpp"

#ifdef NTL_DEBUG
  #define VERIFY(cond) \
  if(!(cond)) {        \
  printf("Verify failed: (%s) -> %s (%s:%d)\n", \
  #cond,       \
  __PRETTY_FUNCTION__,                                                 \
  __FILE__,     \
  __LINE__);      \
  abort();                       \
  }
#else
#define VERIFY(cond)
#endif

#define ENSURE(cond) \
if(!(cond)) {             \
printf("Ensure failed: (%s) -> %s (%s:%d)\n", \
#cond,       \
__PRETTY_FUNCTION__,                                                 \
__FILE__,     \
__LINE__); \
abort();                       \
}                  \

#define CVERIFY(cond) static_assert(cond);

#endif // NTL_ASSERT_HPP
