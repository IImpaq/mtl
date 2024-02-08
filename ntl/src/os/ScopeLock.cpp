/**
* @file ScopeLock.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#include "ScopeLock.hpp"

namespace ntl {
  ScopeLock::ScopeLock(Lock* a_lock)
    : m_lock{a_lock} {
    m_lock->Acquire();
  }

  ScopeLock::~ScopeLock() {
    m_lock->Release();
  }
}
