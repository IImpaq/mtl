/**
* @file Condition.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_CONDITION_HPP
#define NTL_CONDITION_HPP

#include <pthread.h>

#include "os/Lock.hpp"

namespace ntl {
  /**
   * @brief A class that provides synchronization mechanism using condition variables.
   *
   * @note The Condition class currently is just a wrapper around the pthread_cond_t.
   */
  class Condition {
  private:
    pthread_cond_t m_condition;
    Lock* m_lock;

  public:
    /**
     * @brief Deletes the default constructor.
     */
    Condition() = delete;

    /**
     * @brief Creates a new condition using the given lock.
     *
     * @param a_lock the pointer to the lock to be used for the condition
     */
    explicit Condition(Lock* a_lock);

    /**
     * @brief Default Destructor.
     */
    ~Condition();

    /**
     * @brief Deletes Copy Constructor.
     *
     * @param a_other a reference to another condition
     */
    Condition(const Condition& a_other) = delete;

    /**
     * @brief Deletes Copy-Assignment operator.
     *
     * @param a_other a reference to another condition
     *
     * @return the reference to the condition
     */
    Condition& operator=(const Condition& a_other) = delete;

    /**
     * @brief Waits for a condition.
     *
     * @param a_acquire if the condition should re-acquire the lock after waiting
     */
    void Wait(bool a_acquire = true);

    /**
     * @brief Signals the condition to a single waiting thread.
     */
    void Signal();

    /**
     * @brief Signals the condition to all waiting threads.
     */
    void Broadcast();
  };
}

#endif // NTL_CONDITION_HPP
