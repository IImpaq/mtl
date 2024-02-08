/**
* @file Condition.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#include "Condition.hpp"

#include "core/Assert.hpp"

namespace ntl {
  Condition::Condition(Lock* a_lock)
    : m_condition(), m_lock(a_lock) {
    pthread_cond_init(&m_condition, nullptr);
  }

  Condition::~Condition() {
    m_lock = nullptr;
  }

  void Condition::Wait(const bool a_acquire) {
    VERIFY(m_lock && "m_lock shouldn't be a nullptr")

    pthread_cond_wait(&m_condition, &m_lock->m_mutex);

    if (!a_acquire)
      m_lock->Release();
  }

  void Condition::Signal() {
    pthread_cond_signal(&m_condition);
  }

  void Condition::Broadcast() {
    pthread_cond_broadcast(&m_condition);
  }
}
