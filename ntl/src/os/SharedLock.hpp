/**
* @file SharedLock.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_RW_LOCK_HPP
#define NTL_RW_LOCK_HPP

#include <pthread.h>

namespace ntl {
  /**
   * @brief A class that provides advanced synchronization mechanism using mutual-exclusives.
   * The advantage of using SharedMutex over Mutex is that it separates read- and write accesses.
   * This allows simultaneous read accesses while exclusively allowing a single write access.
   *
   * @note The SharedLock class currently is just a wrapper around the pthread_mutex_t in
   * combination with pthread_cond_t to ease safety of critical sections.
   */
  class SharedLock {
  private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_no_writers_left;
    pthread_cond_t m_is_only_access;
    int m_reader_count;
    int m_writer_count;
    bool m_is_writing;

  public:
    /**
     * @brief Default Constructor.
     */
    SharedLock();

    /**
     * @brief Default Destructor.
     */
    ~SharedLock();

    /**
     * @brief Deletes Copy Constructor.
     *
     * @param a_other a reference to another shared mutex
     */
    SharedLock(const SharedLock& a_other) = delete;

    /**
     * @brief Deletes Copy-Assignment operator.
     *
     * @param a_other a reference to another shared mutex
     *
     * @return the reference to the shared mutex
     */
    SharedLock& operator=(const SharedLock& a_other) = delete;

    /**
     * @brief Starts the shared read access. The calling thread will block if the mutex is not available.
     *
     * @details If another thread has already locked the mutex using a write access, a call to lock will
     * block execution until the lock is acquired. On the other hand multiple read accesses are allowed.
     */
    void StartRead();
    /**
     * @brief Starts the exclusive write access. The calling thread will block if the mutex is not available.
     *
     * @details If another thread has already locked the mutex using a write access, a call to lock will
     * block execution until the lock is acquired. On the other hand multiple read accesses are allowed.
     */
    void StartWrite();

    /**
     * @brief Ends the shared read access.
     *
     * @note Releasing a mutex that was acquired by a different thread results in undefined behaviour.
     */
    void EndRead();
    /**
     * @brief Ends the exclusive write access.
     *
     * @note Releasing a mutex that was acquired by a different thread results in undefined behaviour.
     */
    void EndWrite();
  };
}

#endif // NTL_RW_LOCK_HPP
