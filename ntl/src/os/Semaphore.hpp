/**
* @file Semaphore.cpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_SEMAPHORE_HPP
#define NTL_SEMAPHORE_HPP

#include <semaphore.h>

#include "data/Integer.hpp"

namespace ntl {
  /**
   * @brief A class that provides synchronization mechanism using mutual-exclusives.
   *
   * @note The Lock class currently is just a wrapper around the pthread_mutex_t
   */
  class Semaphore {
  private:
    sem_t m_sem;

  public:
    /**
     * @brief Constructs a new semaphore instance.
     *
     * @param a_shared_process if the semaphore should be shared across processes
     * @param a_value the initial value of the semaphore
     */
    Semaphore(bool a_shared_process, U32 a_value);

    /**
     * @brief Default Destructor.
     */
    ~Semaphore();

    /**
     * @brief Deletes Copy Constructor.
     *
     * @param a_other a reference to another mutex
     */
    Semaphore(const Semaphore& a_other) = delete;

    /**
     * @brief Deletes Copy-Assignment operator.
     *
     * @param a_other a reference to another mutex
     *
     * @return the reference to the mutex
     */
    Semaphore& operator=(const Semaphore& a_other) = delete;

   /**
    * @brief Decrements the semaphore. If the semaphore's value is greater
    * than 0, then the method returns right away. If the value is 0, then the
    * functions blacks the calling thread until decrementing is possible.
    *
    * @return Returns true if the semaphore waited successfully, otherwise returns false.
    */
    bool Wait();
    /**
     * @brief Increments the semaphore. If the semaphore's value was 0, then
     * another thread/process will be woken up.
     *
     * @return Returns true if the semaphore posted successfully, otherwise returns false.
     */
    bool Post();

    /**
     * @brief Gets the value of the semaphore.
     *
     * @note Returns -1 on error.
     *
     * @return the value of the semaphore
     */
    I64 GetValue();
  };
}

#endif // NTL_SEMAPHORE_HPP
