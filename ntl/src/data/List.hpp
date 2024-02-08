/**
* @file List.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_LIST_HPP
#define NTL_LIST_HPP

#include "core/Algorithms.hpp"
#include "core/Assert.hpp"
#include "data/Integer.hpp"
#include "data/Size.hpp"
#include "data/String.hpp"

namespace ntl {
  /**
   * @brief Constructs a new linked list object.
   * @tparam T the type of the elements to store
   */
  template<typename T>
  class List {
  public:
    /**
     * @brief Represents a single element in the linked list.
     */
    struct Node {
      T     value;
      Node* next;
    };

    /**
     * @brief Iterator class to simplify iteration over the linked list.
     */
    class Iterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type   = std::ptrdiff_t;
      using value_type        = Node;
      using pointer           = Node*;
      using reference         = Node&;

    private:
      pointer m_ptr;

    public:
      /**
       * @brief Constructs a new iterator
       * @param a_ptr a pointer
       */
      Iterator(pointer a_ptr) : m_ptr(a_ptr) {}

      /**
       * @brief Overloading reference operator.
       * @return the reference to the value of the current iteration
       */
      T& operator*() const { return m_ptr->value; }
      /**
       * @brief Overloading pointer operator.
       * @return the pointer to the value of the current iteration
       */
      T* operator->() { return &m_ptr->value; }
      /**
       * @brief Overloading increment operator.
       * @return the reference to the next iterator
       */
      Iterator& operator++() {
        m_ptr = m_ptr->next;
        return *this;
      }
      /**
       * @brief Overloading increment operator.
       * @return the next iterator
       */
      const Iterator operator++(T) {
        Iterator temp = *this;
        (*this).m_ptr = (*this).m_ptr->next;
        return temp;
      }
      /**
       * @brief Overloading equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both iterators are equivalent
       */
      friend bool operator==(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr == a_second.m_ptr;
      }
      /**
       * @brief Overloading anti equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both iterators aren't equivalent
       */
      friend bool operator!=(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr != a_second.m_ptr;
      }
    };

  private:
    Node*  m_head,
        *  m_tail;
    Size   m_size;

  public:
    /**
     * @brief Constructs a new linked list with the given parameters.
     */
    List();

    /**
     * @brief Constructs a new linked list from another linked list.
     *
     * @details Runtime: O(n), where n is the size of the passed linked list.
     *
     * @param a_other the other linked list
     */
    List(const List<T>& a_other);

    /**
     * @brief Destructs the linked list.
     */
    ~List();

    /**
     * @brief Inserts a new element at the front of the linked list.
     *
     * @details Runtime: O(1)
     *
     * @param a_element the element
     */
    const Node* InsertFront(const T& a_element);
    /**
     * @brief Inserts a new element at the back of the linked list.
     *
     * @details Runtime: O(1)
     *
     * @param a_element the element
     */
    const Node* InsertBack(const T& a_element);
    /**
     * @brief Inserts a new element after a given node of the linked list.
     *
     * @details Runtime: O(1)
     *
     * @param a_node the node after which the element is to be inserted
     * @param a_element the element to insert
     */
    const Node* InsertAfter(const Node* a_node, const T& a_element);

    /**
     * @brief Removes a element from the linked list.
     *
     * @details Runtime: O(n), where n is the size of the linked list.
     *
     * @param a_element the element to remove
     * @return if an element was removed from the linked list
     */
    bool RemoveElement(const T& a_element);
    /**
     * @brief Removes the element after a given node from the linked list.
     *
     * @details Runtime: O(1)
     *
     * @param a_node the node after which the element is to be removed
     */
    void RemoveAfter(const Node* a_node);

    /**
     * @brief Removes all elements from the linked list.
     *
     * @details Runtime: O(n), where n is the size of the linked list
     */
    void Clear();

    /**
     * @brief Finds the node at which a given element is stored.
     *
     * @details Runtime: O(n), where n is the size of the linked list
     *
     * @param a_element the element to find
     * @return the node of the given element
     */
    const Node* FindElement(const T& a_element) const;

    /**
     * @brief Checks if the linked list is equal to another linked list.
     *
     * @details Runtime:
     *  - O(n), where n is the size of the linked list.
     *  - Ω(1), when both linked lists have a different size.
     *
     * @param a_other the other linked list to compare with
     * @return if the linked lists are equal
     */
    bool IsEqual(const List<T>& a_other) const;

    /**
     * @brief Gets the head node.
     *
     * @details Runtime: O(1)
     *
     * @return the pointer to the head node
     *
     * @note this node doesn't contain any data and just specifies the
     * starting point of the linked list
     */
    const Node* GetHead() const;
    /**
     * @brief Gets the first usable node.
     *
     * @details Runtime: O(1)
     *
     * @return the pointer to the first usable node
     */
    const Node* GetFront() const;
    /**
     * @brief Gets the last usable node.
     *
     * @details Runtime: O(1)
     *
     * @return the pointer to the last usable node
     */
    const Node* GetBack() const;
    /**
     * @brief Checks if the linked list is empty.
     *
     * @details Runtime: O(1)
     *
     * @return if the linked list is empty
     */
    [[nodiscard]] bool IsEmpty() const;

    /**
     * @brief Gets the used size of the linked list.
     *
     * @details Runtime: O(1)
     *
     * @return the used size
     */
    [[nodiscard]] Size GetSize() const;

    /**
     * @brief Gets the data stored in the linked list.
     *
     * @details Runtime: O(1)
     *
     * @return the data
     */
    [[nodiscard]] const Node* GetData() const;

    /**
     * @brief Overloading equivalence operator.
     * @param a_other the linked list to compare with
     * @return if both linked lists are equivalent
     */
    bool operator==(const List& a_other) const;

    /**
     * @brief Overloading anti equivalence operator.
     * @param a_other the linked list to compare with
     * @return if both linked list aren't equivalent
     */
    bool operator!=(const List& a_other) const;

    /**
     * @brief Converts the linked list to a string.
     *
     * @details Runtime: O(n), where n is the size of the linked list.
     *
     * @return the linked list as a string
     */
    [[nodiscard]] String ToString() const;

    /**
     * @brief Gets the beginning of the iterator.
     * @return the iterator at the beginning
     */
    Iterator begin();
    /**
     * @brief Gets the end of the iterator.
     * @return the iterator at the end
     */
    Iterator end();
  };

  // ------------------------
  // ITERATOR-RELATED METHODS
  // ------------------------

  template<typename T>
  typename List<T>::Iterator List<T>::begin() {
    return List::Iterator(m_head->next);
  }

  template<typename T>
  typename List<T>::Iterator List<T>::end() {
    return List::Iterator(m_tail->next);
  }

  // ---------------------------
  // GLOBAL OVERLOADED OPERATORS
  // ---------------------------

  /**
   * @brief Overloading the left shift operator.
   * @param a_stream the ostream
   * @param a_list the list
   * @return the combined ostream
   */
  template<typename T>
  std::ostream& operator<<(std::ostream& a_stream, const List<T>& a_list) {
    return (a_stream << a_list.ToString());
  }

  // --------------
  // PUBLIC METHODS
  // --------------

  template<typename T>
  List<T>::List()
    : m_head{new Node}, m_size{0} {
    m_head->next = nullptr;
    m_tail = m_head;
  }

  template<typename T>
  List<T>::List(const List& a_other)
    : m_head{new Node}, m_tail{nullptr}, m_size(a_other.m_size) {
    auto* curr1 = m_head;
    auto* curr2 = a_other.m_head;
    while(curr2->next) {
      curr2 = curr2->next;
      auto* node = new Node;
      curr1->next = node;
      node->next = nullptr;
      node->value = curr2->value;
      curr1 = node;
    }
    m_tail = curr1;
  }

  template<typename T>
  List<T>::~List() {
    Clear();
  }

  template<typename T>
  const typename List<T>::Node* List<T>::InsertFront(const T& a_element) {
    auto* result = new Node;

    if(!m_head->next)
      m_tail = result;

    result->value = a_element;
    result->next = m_head->next;
    m_head->next = result;


    m_size++;

    return result;
  }

  template<typename T>
  const typename List<T>::Node* List<T>::InsertBack(const T& a_element) {
    auto* result = new Node;
    result->value = a_element;
    result->next = nullptr;
    m_tail->next = result;
    m_tail = result;

    m_size++;

    return result;
  }

  template<typename T>
  const typename List<T>::Node* List<T>::InsertAfter(const Node* a_node, const T& a_element) {
    VERIFY(a_node != nullptr)

    auto* node = const_cast<Node*>(a_node);
    auto* result = new Node;

    result->value = a_element;
    result->next = node->next;

    if(!node->next)
      m_tail = result;

    node->next = result;

    m_size++;

    return result;
  }

  template<typename T>
  bool List<T>::RemoveElement(const T& a_element) {
    auto* curr = m_head;
    bool success = false;

    while(curr->next) {
      if(curr->next->value == a_element) {
        auto* temp = curr->next->next;
        delete curr->next;
        curr->next = temp;

        if(!curr->next)
          m_tail = curr;

        success = true;
        break;
      }
      curr = curr->next;
    }

    m_size--;

    return success;
  }

  template<typename T>
  void List<T>::RemoveAfter(const Node* a_node) {
    VERIFY(a_node != nullptr)
    VERIFY(a_node->next != nullptr)

    auto* node = const_cast<Node*>(a_node);
    auto* temp = node->next->next;
    delete node->next;
    node->next = temp;

    if(!node->next)
      m_tail = node;

    m_size--;
  }

  template<typename T>
  void List<T>::Clear() {
    auto* curr = m_head->next;

    while(curr) {
      auto* tmp = curr->next;
      delete curr;
      curr = tmp;
    }

    m_head->next = nullptr;
    m_size = 0;
  }

  template<typename T>
  const typename List<T>::Node* List<T>::FindElement(const T& a_element) const {
    auto* curr = m_head;

    while(curr->next) {
      curr = curr->next;
      if(curr->value == a_element) {
        break;
      }
    }

    return curr == m_head ? nullptr : curr;
  }

  template<typename T>
  const typename List<T>::Node* List<T>::GetHead() const {
    return m_head;
  }

  template<typename T>
  const typename List<T>::Node* List<T>::GetFront() const {
    return m_head->next;
  }

  template<typename T>
  const typename List<T>::Node* List<T>::GetBack() const {
    return m_tail;
  }

  template<typename T>
  bool List<T>::IsEmpty() const {
    return (!m_head->next);
  }

  template<typename T>
  Size List<T>::GetSize() const {
    return m_size;
  }

  template<typename T>
  bool List<T>::IsEqual(const List& a_other) const {
    if(m_size != a_other.m_size)
      return false;

    bool result = true;
    auto* curr1 = m_head;
    auto* curr2 = a_other.m_head;

    while(curr1->next && curr2->next) {
      if(curr1->next->value != curr2->next->value) {
        result = false;
        break;
      }

      curr1 = curr1->next;
      curr2 = curr2->next;
    }

    return result;
  }

  template<typename T>
  const typename List<T>::Node* List<T>::GetData() const {
    return m_head;
  }

  template<typename T>
  bool List<T>::operator==(const List& a_other) const {
    return IsEqual(a_other);
  }

  template<typename T>
  bool List<T>::operator!=(const List& a_other) const {
    return (!IsEqual(a_other));
  }

  template<typename T>
  String List<T>::ToString() const {
    String result = "List(";
    auto* curr = m_head;

    while(true) {
      curr = curr->next;
      result += curr->value;

      if(!curr->next) {
        result += ")\n";
        break;
      }

      result += ", ";
    }

    return result;
  }
}

#endif // NTL_LIST_HPP
