/**
* @file Stack.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_STACK_HPP
#define NTL_STACK_HPP

#include "data/List.hpp"

namespace ntl {
  /**
   * @brief Constructs a new stack object.
   * @tparam T the type of the elements to store
   */
  template<typename T>
  class Stack {
  private:
    List<T> m_data;

  public:
    /**
     * @brief Constructs a new stack.
     *
     * @details Runtime: O(n), where n is the size of the linked list
     *
     * @note Uses a linked list internally.
     */
    Stack();

    /**
     * @brief Destroys the stack.
     */
    ~Stack() = default;

    /**
     * @brief Pushes a new element onto the top of the stack.
     *
     * @details Runtime: O(1)
     *
     * @param a_element the element to add
     *
     * @note Uses InsertFront to add the new element to the internal linked list.
     */
    void Push(const T& a_element);

    /**
     * @brief Removes the top element from the stack and returns it.
     *
     * @details Runtime: O(1)
     *
     * @return the element that was removed from the top of the stack
     *
     * @note Uses GetFront and RemoveAfter to remove the element from the
     * internal linked list.
     */
    T Pop();

    /**
     * @brief Peeks at the element on top of the stack.
     *
     * @details Runtime: O(1)
     *
     * @return the element that is currently on top of the stack
     *
     * @note Uses GetFront to get the element from the internal linked list.
     */
    const T& Peek() const;

    /**
     * @brief Gets the size of the stack.
     *
     * @details Runtime: O(1)
     *
     * @return the size of the stack
     *
     * @note The internal linked list counts the number of elements
     * to avoid unnecessary recalculations.
     */
    [[nodiscard]] Size GetSize() const;

    /**
     * @brief Checks if the stack is empty.
     *
     * @details Runtime: O(1)
     *
     * @return if the stack is empty
     */
    [[nodiscard]] bool IsEmpty() const;
  };

  template<typename T>
  Stack<T>::Stack()
    : m_data{List<T>()} {}

  template<typename T>
  void Stack<T>::Push(const T& a_element) {
    m_data.InsertFront(a_element);
  }

  template<typename T>
  T Stack<T>::Pop() {
    T result = m_data.GetFront()->value;
    m_data.RemoveAfter(m_data.GetHead());
    return result;
  }

  template<typename T>
  const T& Stack<T>::Peek() const {
    return m_data.GetFront()->value;
  }

  template<typename T>
  Size Stack<T>::GetSize() const {
    return m_data.GetSize();
  }

  template<typename T>
  bool Stack<T>::IsEmpty() const {
    return m_data.IsEmpty();
  }
}

#endif // NTL_STACK_HPP
