/**
* @file ScopeLock.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_SCOPE_LOCK_HPP
#define NTL_SCOPE_LOCK_HPP

#include "os/Lock.hpp"

namespace ntl {
  /**
   * @brief A class that provides synchronization mechanism using mutual-exclusives.
   */
  class ScopeLock {
    Lock* m_lock;

  public:
    /**
     * @brief Default Constructor,
     */
    explicit ScopeLock(Lock* a_lock);

    /**
     * @brief Default Destructor.
     */
    ~ScopeLock();

    /**
     * @brief Deletes Copy Constructor.
     *
     * @param a_other a reference to another mutex
     */
    ScopeLock(const ScopeLock& a_other) = delete;

    /**
     * @brief Deletes Copy-Assignment operator.
     *
     * @param a_other a reference to another mutex
     *
     * @return the reference to the mutex
     */
    ScopeLock& operator=(const ScopeLock& a_other) = delete;
  };
}

#endif // NTL_SCOPE_LOCK_HPP
