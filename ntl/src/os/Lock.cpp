/**
* @file Lock.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#include "Lock.hpp"

namespace ntl {
  Lock::Lock() : m_mutex() {
    pthread_mutex_init(&m_mutex, nullptr);
  }

  Lock::~Lock() {
    pthread_mutex_destroy(&m_mutex);
  }

  void Lock::Acquire() {
    pthread_mutex_lock(&m_mutex);
  }

  bool Lock::TryAcquire() {
    return pthread_mutex_trylock(&m_mutex);
  }

  void Lock::Release() {
    pthread_mutex_unlock(&m_mutex);
  }
}
