/**
* @file Integer.hpp
* @author Marcus Gugacs
* @date 02/07/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_INTEGER_HPP
#define NTL_INTEGER_HPP

#include <cstdint>

namespace ntl {
  // unsigned integer
  typedef std::uint8_t U8;
  typedef std::uint16_t U16;
  typedef std::uint32_t U32;
  typedef std::uint64_t U64;

  // Signed integer
  typedef std::int8_t I8;
  typedef std::int16_t I16;
  typedef std::int32_t I32;
  typedef std::int64_t I64;

  // Pointer
  typedef intptr_t IPtr;
  typedef uintptr_t UPtr;
}

#endif // NTL_INTEGER_HPP
