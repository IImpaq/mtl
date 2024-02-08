/**
* @file Queue.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_QUEUE_HPP
#define NTL_QUEUE_HPP

#include "data/List.hpp"

namespace ntl {
  /**
   * @brief Constructs a new queue object.
   * @tparam T the type of the elements to store
   */
  template<typename T>
  class Queue {
  private:
    List<T> m_data;

  public:
    /**
     * @brief Constructs a new queue.
     *
     * @details Runtime: O(n), where n is the size of the linked list
     *
     * @note Uses a linked list internally.
     */
    Queue();

    /**
     * @brief Destroys the queue.
     */
    ~Queue() = default;

    /**
     * @brief Puts a new element at the end of the queue.
     *
     * @details Runtime: O(1)
     *
     * @param a_element the element to add
     *
     * @note Uses InsertBack to add the new element to the internal linked list.
     */
    void Put(const T& a_element);

    /**
     * @brief Removes the first/oldest element from the queue and returns it.
     *
     * @details Runtime: O(1)
     *
     * @return the element that was removed from the start of the queue
     *
     * @note Uses GetFront and RemoveAfter to remove the element from the
     * internal linked list.
     */
    T Get();

    /**
     * @brief Peeks at the element first/oldest element in the queue.
     *
     * @details Runtime: O(1)
     *
     * @return the element that is at the start of the queue
     *
     * @note Uses GetFront to get the element from the internal linked list.
     */
    const T& Peek() const;

    /**
     * @brief Gets the size of the queue.
     *
     * @details Runtime: O(1)
     *
     * @return the size of the queue
     *
     * @note The internal linked list counts the number of elements
     * to avoid unnecessary recalculations.
     */
    [[nodiscard]] Size GetSize() const;

    /**
     * @brief Checks if the queue is empty.
     *
     * @details Runtime: O(1)
     *
     * @return if the queue is empty
     */
    [[nodiscard]] bool IsEmpty() const;
  };

  template<typename T>
  Queue<T>::Queue()
    : m_data{List<T>()} {}

  template<typename T>
  void Queue<T>::Put(const T& a_element) {
    m_data.InsertBack(a_element);
  }

  template<typename T>
  T Queue<T>::Get() {
    T result = m_data.GetFront()->value;
    m_data.RemoveAfter(m_data.GetHead());
    return result;
  }

  template<typename T>
  const T& Queue<T>::Peek() const {
    return m_data.GetFront()->value;
  }

  template<typename T>
  Size Queue<T>::GetSize() const {
    return m_data.GetSize();
  }

  template<typename T>
  bool Queue<T>::IsEmpty() const {
    return m_data.IsEmpty();
  }
}

#endif // NTL_QUEUE_HPP
