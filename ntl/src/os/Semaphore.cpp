/**
* @file Semaphore.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#include "Semaphore.hpp"

namespace ntl {
  Semaphore::Semaphore(const bool a_shared_process, const U32 a_value)
    : m_sem() {
    sem_init(&m_sem, a_shared_process ? 0 : 1, a_value);
  }

  Semaphore::~Semaphore() {
    sem_destroy(&m_sem);
  }

  bool Semaphore::Wait() {
    return (sem_wait(&m_sem) == 0);
  }

  bool Semaphore::Post() {
    return (sem_post(&m_sem) == 0);
  }

  I64 Semaphore::GetValue() {
    int value = -1;
    sem_getvalue(&m_sem, &value);
    return value;
  }
}
