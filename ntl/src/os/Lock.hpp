/**
* @file Lock.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_LOCK_HPP
#define NTL_LOCK_HPP

#include <pthread.h>

namespace ntl {
  class Condition;

  /**
   * @brief A class that provides synchronization mechanism using mutual-exclusives.
   *
   * @note The Lock class currently is just a wrapper around the pthread_mutex_t
   */
  class Lock {
  private:
    pthread_mutex_t m_mutex;

  public:
    /**
     * @brief Default Constructor,
     */
    Lock();
    /**
     * @brief Default Destructor.
     */
    ~Lock();
    /**
     * @brief Deletes Copy Constructor.
     *
     * @param a_other a reference to another mutex
     */
    Lock(const Lock& a_other) = delete;
    /**
     * @brief Deletes Copy-Assignment operator.
     *
     * @param a_other a reference to another mutex
     *
     * @return the reference to the mutex
     */
    Lock& operator=(const Lock& a_other) = delete;
    /**
     * @brief Locks the mutex. The calling thread will block if the mutex is not available.
     *
     * @details If another thread has already locked the mutex, a call to lock will
     * block execution until the lock is acquired.
     */
    void Acquire();
    /**
     * @brief Attempts to lock the mutex.
     *
     * @return Returns true if the lock was acquired successfully, otherwise returns false.
     */
    bool TryAcquire();
    /**
     * @brief Unlocks the mutex.
     *
     * @note Releasing a mutex that was acquired by a different thread results in undefined behaviour.
     */
    void Release();
  };
}

#endif // NTL_LOCK_HPP
