/**
* @file Real.hpp
* @author Marcus Gugacs
* @date 02/07/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_REAL_HPP
#define NTL_REAL_HPP

namespace ntl {
#if NTL_DOUBLE_PRECISION
  typedef double Real;
#else
  typedef float Real;
#endif
}

#endif // NTL_REAL_HPP
