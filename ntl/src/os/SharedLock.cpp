/**
* @file SharedLock.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#include "SharedLock.hpp"

namespace ntl {
  SharedLock::SharedLock()
    : m_mutex(), m_no_writers_left(), m_is_only_access(), m_reader_count(0), m_writer_count(0), m_is_writing(false) {
    pthread_mutex_init(&m_mutex, nullptr);
    pthread_cond_init(&m_is_only_access, nullptr);
    pthread_cond_init(&m_no_writers_left, nullptr);
  }

  SharedLock::~SharedLock() {
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_is_only_access);
    pthread_cond_destroy(&m_no_writers_left);
  }

  void SharedLock::StartRead() {
    pthread_mutex_lock(&m_mutex);

    while (m_writer_count != 0) {
      pthread_cond_wait(&m_no_writers_left, &m_mutex);
    }
    ++m_reader_count;

    pthread_mutex_unlock(&m_mutex);
  }

  void SharedLock::StartWrite() {
    pthread_mutex_lock(&m_mutex);

    // incrementing writer count before waiting to avoid writers starvation
    ++m_writer_count;
    while (m_reader_count != 0 || m_is_writing) {
      pthread_cond_wait(&m_is_only_access, &m_mutex);
    }
    m_is_writing = true;

    pthread_mutex_unlock(&m_mutex);
  }

  void SharedLock::EndRead() {
    pthread_mutex_lock(&m_mutex);

    --m_reader_count;
    if (m_reader_count == 0 && m_writer_count > 0)
      pthread_cond_broadcast(&m_is_only_access);

    pthread_mutex_unlock(&m_mutex);
  }

  void SharedLock::EndWrite() {
    pthread_mutex_lock(&m_mutex);

    --m_writer_count;
    m_is_writing = false;
    if (m_writer_count > 0)
      pthread_cond_broadcast(&m_is_only_access);
    else
      pthread_cond_broadcast(&m_no_writers_left);

    pthread_mutex_unlock(&m_mutex);
  }
}
