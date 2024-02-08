/**
* @file Array.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_ARRAY_HPP
#define NTL_ARRAY_HPP

#include "core/Algorithms.hpp"
#include "core/Assert.hpp"
#include "data/Integer.hpp"
#include "data/Size.hpp"
#include "data/String.hpp"

namespace ntl {
  /**
   * @brief Constructs a new static/dynamic array object.
   * @tparam T the type of the elements to store
   */
  template<typename T>
  class Array {
  public:
    // workaround to avoid the constructor of the
    // object "T" being called. Also allows the usage
    // of the auto alignment feature of the new operator

    /**
     * @brief Represents a single element in the array.
     */
    union ArrayChunk {
      T value;

      ArrayChunk() {}

      ~ArrayChunk() {}
    };

    /**
     * @brief Iterator class to simplify iteration over array.
     */
    class Iterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = T;
      using pointer = ArrayChunk*;
      using reference = ArrayChunk&;

    private:
      pointer m_ptr;

    public:
      /**
       * @brief Constructs a new iterator
       * @param a_ptr a pointer
       */
      Iterator(pointer a_ptr)
        : m_ptr(a_ptr) {
        // Empty
      }

      /**
       * @brief Overloading reference operator.
       * @return the reference to the value of the current iteration
       */
      value_type& operator*() const { return m_ptr->value; }
      /**
       * @brief Overloading pointer operator.
       * @return the pointer to the value of the current iteration
       */
      value_type* operator->() { return &m_ptr->value; }
      /**
       * @brief Overloading increment operator.
       * @return the reference to the next iterator
       */
      Iterator& operator++() {
        m_ptr++;
        return *this;
      }

      /**
       * @brief Overloading increment operator.
       * @return the next iterator
       */
      const Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
      }

      /**
       * @brief Overloading decrement operator.
       * @return the previous iterator
       */
      Iterator& operator--() {
        m_ptr--;
        return *this;
      }

      /**
       * @brief Overloading decrement operator.
       * @return the next iterator
       */
      const Iterator operator--(int) {
        Iterator temp = *this;
        --(*this);
        return temp;
      }

      /**
       * @brief Overloading equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors are equivalent
       */
      friend bool operator==(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr == a_second.m_ptr;
      }

      /**
       * @brief Overloading anti equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors aren't equivalent
       */
      friend bool operator!=(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr != a_second.m_ptr;
      }

      /**
       * @brief Overloading anti greater-than operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors aren't equivalent
       */
      friend bool operator>(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr > a_second.m_ptr;
      }

      /**
       * @brief Overloading anti less-than operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors aren't equivalent
       */
      friend bool operator<(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr < a_second.m_ptr;
      }
    };

  private:
    ArrayChunk* m_data;
    Size m_used,
        m_capacity;
    bool m_sorted,
        m_keep_sorted,
        m_growable;

  public:
    /**
     * @brief Constructs a new array with the given parameters.
     *
     * The default capacity of the array is 1024 with auto sorting disabled
     * and automatic resizing disabled.
     *
     * @param a_capacity the maximum capacity
     * @param a_keep_sorted if the array should be kept sorted
     * @param a_growable if the array should be able to grow when maximum capacity is reached
     */
    explicit Array(Size a_capacity = 1024, bool a_keep_sorted = false, bool a_growable = false);

    /**
     * @brief Constructs a new array from another array with double its used size as capacity.
     *
     * @details Runtime: O(n), where n is the used size of the passed array.
     *
     * @param a_other the other array
     */
    Array(const Array<T>& a_other);

    /**
     * @brief Constructs a new array from another array with a given capacity.
     *
     * @details Runtime: O(n), where n is the used size of the passed array.
     *
     * @param a_other the other array
     * @param a_capacity the maximum capacity
     */
    Array(const Array<T>& a_other, Size a_capacity);

    /**
     * @brief Destructs the array.
     */
    ~Array();

    /**
     * @brief Inserts a new element at the end of the array.
     *
     * @details Runtime:
     *  - O(n), where n is the used size of the array. n is a result of resizing when necessary.
     *  - Ω(1), in the best and average case
     *
     * @param a_element the element
     * @return the index of the element
     */
    Size Insert(const T& a_element);

    /**
     * @brief Inserts a new element at a given index (between 0 and used size).
     *
     * @details Runtime: O(n), where n is the used size of the array. n is a result of either
     * reallocation or element shifting.
     *
     * @param a_element the element
     * @param a_index the index to insert at
     */
    void Insert(const T& a_element, Size a_index);

    /**
     * @brief Removes a element from the array.
     *
     * @details Runtime: O(n), where n is the used size of the array. n is either the result
     * of finding the element to remove or element shifting.
     *
     * @param a_element the element to remove
     * @return the index where the element was removed from (-1 if not found)
     *
     * @note In practice the runtime will be lower if the array is sorted.
     */
    I64 RemoveElement(const T& a_element);

    /**
     * @brief Removes the element at the given index from the array.
     *
     * @details Runtime: O(n), where n is the used size of the array. n is the result of
     * shifting the elements to fill gaps.
     *
     * @param a_index the index where the element to remove is
     * @return the element that was removed
     */
    const T& Remove(Size a_index);

    /**
     * @brief Swaps two elements at the given indices.
     *
     * @details Runtime: O(1)
     *
     * @param a_first the index of the first element
     * @param a_second the index of the second element
     */
    void Swap(Size a_first, Size a_second);

    /**
     * @brief Removes all elements from the array.
     *
     * @details Runtime: O(1)
     */
    void Clear();

    /**
     * @brief Removes all elements from the array and updates its maximum capacity.
     *
     * @details Runtime: O(1)
     *
     * @param a_capacity the new maximum capacity
     */
    void Clear(Size a_capacity);

    /**
     * @brief Resizes the array to a new given capacity.
     *
     * @details Runtime: O(n), where n is the used size of the array. n is the result of moving
     * the existing elements to the newly allocated array.
     *
     * @param a_capacity the new capacity to resize to
     */
    void Resize(Size a_capacity);

    /**
     * @brief Sorts the array using the given sorting algorithm.
     *
     * @details Runtime:
     *  - DynamicSort: O(n*log(n)) & Ω(n), where n is the used size of the array.
     *  - InsertionSort: O(n^2) & Ω(n), where n is the used size of the array.
     *  - QuickSort: O(n^2) & Ω(n*log(n)), where n is the used size of the array.
     *  - MergeSort O(n*log(n)) & Ω(n*log(n)), where n is the used size of the array.
     *
     * @param a_algorithm the sorting algorithm to use
     */
    void Sort(algorithms::Sort a_algorithm = algorithms::Sort::DYNAMIC);

    /**
     * @brief Finds the index of a given element in the array.
     *
     * @details Runtime:
     *  - Sorted: O(log(n)), where n is the used size of the array.
     *  - Unsorted: O(n), where n is the used size of the array.
     *
     * @param a_element the element to find
     * @return the index of the element (-1 if not found)
     */
    I64 Find(const T& a_element) const;

    /**
     * @brief Finds the index of a given element in the subarray specified by the given indices.
     *
     * @details Runtime:
     *  - BinarySearch: O(log(n)), where n is the used size of the array.
     *  - FrontBackSearch: O(n), where n is the used size of the array.
     *
     * @param a_element the element to find
     * @param a_from the starting index to search from
     * @param a_to the ending index to search to
     * @param a_algorithm the algorithm to use for searching
     * @return the index of the element (-1 if not found)
     *
     * @note the binary search algorithm can only be used if the array is sorted
     */
    I64 Find(const T& a_element, I64 a_from, I64 a_to,
             algorithms::Search a_algorithm = algorithms::Search::BINARY_SEARCH) const;

    /**
     * @brief Gets the element at the given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the element
     * @return the element itself
     */
    const T& Get(Size a_index) const;

    /**
     * @brief Gets the element at the given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the element
     * @return the element itself
     */
    T& Get(Size a_index);

    /**
     * @brief Gets the first element.
     *
     * @details Runtime: O(1)
     *
     * @return the element itself
     */
    const T& GetFirst() const;

    /**
     * @brief Gets the first element.
     *
     * @details Runtime: O(1)
     *
     * @return the element itself
     */
    T& GetFirst();

    /**
     * @brief Gets the last element.
     *
     * @details Runtime: O(1)
     *
     * @return the element itself
     */
    const T& GetLast() const;

    /**
     * @brief Gets the last element.
     *
     * @details Runtime: O(1)
     *
     * @return the element itself
     */
    T& GetLast();

    /**
     * @brief Gets the neighbors of a given elements.
     *
     * @details Runtime:
     *  - Sorted: O(log(n)), where n is the used size of the array.
     *  - Unsorted: O(n), where n is the used size of the array.
     *
     * @param[in] a_element the element to get the neighbors of
     * @param[out] a_left where to store the left neighbor
     * @param[out] a_right where to store the right neighbor
     * @note The runtime is a result of the internal usage of the Find method.
     */
    void GetNeighbors(const T& a_element, T*& a_left, T*& a_right);


    /**
     * @brief Gets a specific subarray within the array.
     *
     * @details Runtime: O(n), where n = a_to - a_from.
     *
     * @param a_from the starting index
     * @param a_to the ending index
     * @return the requested subarray
     *
     * @note the caller is responsible for freeing the newly allocated memory
     */
    Array<T> GetSubArray(Size a_from, Size a_to) const;

    /**
     * @brief Checks if the array is equal to another array.
     *
     * @details Runtime: O(n), where n is the used size of the array.
     *
     * @param a_other the other array to compare with
     * @return if the arrays are equal
     */
    bool IsEqual(const Array<T>& a_other) const;

    /**
     * @brief Checks if the array is empty.
     *
     * @details Runtime: O(1)
     *
     * @return if the array is empty
     */
    [[nodiscard]] bool IsEmpty() const;

    /**
     * @brief Gets the capacity of the array.
     *
     * @details Runtime: O(1)
     *
     * @return the capacity
     */
    [[nodiscard]] Size GetCapacity() const;

    /**
     * @brief Gets how much size is occupied in the array.
     *
     * @details Runtime: O(1)
     *
     * @return the used size
     */
    [[nodiscard]] Size GetSize() const;

    /**
     * @brief Gets the data stored in the array.
     *
     * @details Runtime: O(1)
     *
     * @return the data
     */
    [[nodiscard]] T* GetData() const;

    /**
     * @brief Overloading subscript operator.
     * @param a_index the index of a element
     * @return the reference to the element at the given index
     */
    T& operator[](Size a_index);

    /**
     * @brief Overloading const subscript operator.
     * @param a_index the index of a element
     * @return the const reference to the element at the given index
     */
    const T& operator[](Size a_index) const;

    /**
     * @brief Overloading addition assignment operator.
     * @param a_element the element to add
     * @return the reference of the current array object
     */
    Array& operator+=(const T& a_element);

    /**
     * @brief Overloading subtraction assignment operator.
     * @param a_element the element to remove
     * @return the reference of the current array object
     */
    Array& operator-=(const T& a_element);

    /**
     * @brief Overloading equivalence operator.
     * @param a_other the array to compare with
     * @return if both arrays are equivalent
     */
    bool operator==(const Array& a_other) const;

    /**
     * @brief Overloading anti equivalence operator.
     * @param a_other the array to compare with
     * @return if both arrays aren't equivalent
     */
    bool operator!=(const Array& a_other) const;

    /**
     * @brief Converts the array to a string.
     *
     * @details Runtime: O(n), where n is the used size of the array.
     *
     * @return the array as a string
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

  private:
    /**
     * @brief Searches the array using the binary search algorithm.
     *
     * @details Runtime O(log(n)), where is the used size of the array.
     *
     * @param a_element the element to find
     * @param a_from the starting index to search from
     * @param a_to the ending index to search to
     * @return the index of the found element (-1 if not found)
     */
    I64 binarySearch(const T& a_element, I64 a_from, I64 a_to) const;

    /**
     * @brief Searches the array using the front and back search algorithm
     *
     * @details Runtime: O(n), where n is the used size of the array.
     *
     * @param a_element the element to find
     * @param a_from the starting index to search from
     * @param a_to the ending index to search to
     * @return the index of the found element (-1 if not found)
     *
     * @note in practice it's probably faster than O(n) as it will only search
     * half of the used size of the array.
     */
    I64 frontBackSearch(const T& a_element, I64 a_from, I64 a_to) const;

    /**
     * @brief Sorts the array using the insertion sort algorithm.
     *
     * @details Runtime: O(n^2) & Ω(n), where n is the used size of the array.
     */
    void insertionSort();

    /**
     * @brief Sorts the array using the quick sort algorithm.
     *
     * @details Runtime: O(n^2) & Ω(n*log(n)), where n is the used size of the array.
     *
     * @param a_from the starting index to sort from
     * @param a_to the ending index to sort to
     */
    void quickSort(I64 a_from, I64 a_to);

    /**
     * @brief Sorts the whole array using the quick sort algorithm.
     *
     * @details Runtime: O(n*log(n)) & Ω(n*log(n)), where n is the used size of the array.
     */
    void mergeSort();

    /**
     * @brief Sorts the array using the merge sort algorithm.
     *
     * @details Runtime: O(n*log(n)) & Ω(n*log(n)), where n is the used size of the array.
     *
     * @param a_array the array to sort
     * @param a_capacity the capacity of the array
     * @param a_used the used size of the array
     * @return the sorted part of the array
     */
    ArrayChunk* mergeSort(ArrayChunk* a_array, I64 a_capacity, I64 a_used);

    /**
     * @brief Sorts the array using a dynamic sorting algorithm.
     *
     * @details Runtime: O(n*log(n)) & Ω(n), where n is the used size of the array.
     *
     * @note this is inspired by the TimSort algorithm using in Python
     */
    void dynamicSort();

    /**
     * @brief Partitioning the array by selecting a pivot element.
     *
     * @details Runtime O(n), where n is the used size of the array.
     *
     * @param a_from the starting index to partition from
     * @param a_to the ending index to partition to
     * @return the index of the pivot element
     */
    I64 partition(I64 a_from, I64 a_to);
  };

  /*********************************************************************************************************************
   *                                                      ARRAY                                                        *
   *                                                 HELPER FUNCTIONS                                                  *
   ********************************************************************************************************************/

  template<class L, class R=L>
  concept has_bigger_than = requires(const L& a_lhs, const R& a_rhs) {
    { a_lhs > a_rhs } -> std::same_as<bool>;
  };

  template<class L, class R=L>
  concept has_less_than = requires(const L& a_lhs, const R& a_rhs) {
    { a_lhs < a_rhs } -> std::same_as<bool>;
  };

  template<class L, class R=L>
  concept has_less_equals_than = requires(const L& a_lhs, const R& a_rhs) {
    { a_lhs <= a_rhs } -> std::same_as<bool>;
  };

  /*********************************************************************************************************************
   *                                                      ARRAY                                                        *
   *                                             ITERATOR-RELATED METHODS                                              *
   ********************************************************************************************************************/

  template<typename T>
  typename Array<T>::Iterator Array<T>::begin() {
    return Iterator(m_data);
  }

  template<typename T>
  typename Array<T>::Iterator Array<T>::end() {
    return Array::Iterator(m_data + m_used);
  }

  /*********************************************************************************************************************
   *                                                      ARRAY                                                        *
   *                                           GLOBAL OVERLOADED OPERATORS                                             *
   ********************************************************************************************************************/

  /**
   * @brief Overloading the left shift operator.
   * @param a_stream the ostream
   * @param a_array the array
   * @return the combined ostream
   */
  template<typename T>
  std::ostream& operator<<(std::ostream& a_stream, const Array<T>& a_array) {
    return (a_stream << a_array.ToString());
  }

  /*********************************************************************************************************************
   *                                                      ARRAY                                                        *
   *                                                  PUBLIC METHODS                                                   *
   ********************************************************************************************************************/

  template<typename T>
  Array<T>::Array(const Size a_capacity, const bool a_keep_sorted, const bool a_growable)
    : m_data{new ArrayChunk[a_capacity]}, m_used{0}, m_capacity{a_capacity},
      m_sorted{true}, m_keep_sorted(a_keep_sorted), m_growable(a_growable) {
    VERIFY(m_capacity > 0)
  }

  template<typename T>
  Array<T>::Array(const Array& a_other)
    : m_data{new ArrayChunk[a_other.m_capacity]}, m_used(a_other.m_used), m_capacity(m_used * 2),
      m_sorted(a_other.m_sorted), m_keep_sorted(a_other.m_keep_sorted), m_growable(a_other.m_growable) {
    for (Size i = 0; i < m_used; i++) {
      m_data[i].value = a_other.m_data[i].value;
    }
  }

  template<typename T>
  Array<T>::Array(const Array& a_other, const Size a_capacity)
    : m_data{new ArrayChunk[a_capacity]}, m_used(a_other.m_used), m_capacity(a_capacity), m_sorted(a_other.m_sorted),
      m_keep_sorted(a_other.m_keep_sorted), m_growable(a_other.m_growable) {
    VERIFY(m_capacity > m_used)

    for (Size i = 0; i < m_used; i++) {
      m_data[i] = a_other.m_data[i];
    }
  }

  template<typename T>
  Array<T>::~Array() {
    delete[] m_data;
  }

  template<typename T>
  Size Array<T>::Insert(const T& a_element) {
    if (m_growable && m_used >= m_capacity)
      Resize(m_capacity * 2);

    VERIFY(m_used < m_capacity)

    m_data[m_used].value = a_element;
    m_used++;

    if (m_keep_sorted) {
      insertionSort();
    } else {
      m_sorted = false;
    }

    return (m_used - 1);
  }

  template<typename T>
  void Array<T>::Insert(const T& a_element, Size a_index) {
    VERIFY(a_index <= m_used)

    if (a_index >= m_capacity && m_growable)
      Resize(m_capacity * 2);

    VERIFY(a_index < m_capacity)

    for (Size i = m_used; i > a_index; --i) {
      m_data[i] = m_data[i - 1];
    }

    m_data[a_index].value = a_element;
    m_used++;

    if (m_keep_sorted) {
      insertionSort();
    } else {
      m_sorted = false;
    }
  }

  template<typename T>
  I64 Array<T>::RemoveElement(const T& a_element) {
    auto index = Find(a_element);
    if (index < 0)
      return -1;

    Remove(index);
    return index;
  }

  template<typename T>
  const T& Array<T>::Remove(Size a_index) {
    VERIFY(a_index < m_used)

    for (Size i = a_index; i < m_used; i++) {
      m_data[i] = m_data[i + 1];
    }

    m_used--;

    return static_cast<ArrayChunk*>(m_data + a_index)->value;
  }

  template<typename T>
  void Array<T>::Swap(Size a_first, Size a_second) {
    VERIFY(a_first < m_used)
    VERIFY(a_second < m_used)

    auto temp = m_data[a_first];
    m_data[a_first] = m_data[a_second];
    m_data[a_second] = temp;

    m_sorted = false;
  }

  template<typename T>
  void Array<T>::Clear() {
    delete[] m_data;
    m_data = new ArrayChunk[m_capacity];
    m_sorted = true;
    m_used = 0;
  }

  template<typename T>
  void Array<T>::Clear(const Size a_capacity) {
    delete[] m_data;
    m_capacity = a_capacity;
    m_data = new ArrayChunk[m_capacity];
    m_sorted = true;
    m_used = 0;
  }

  template<typename T>
  void Array<T>::Resize(const Size a_capacity) {
    VERIFY(a_capacity >= m_used);
    VERIFY(a_capacity > m_capacity)

    m_capacity = a_capacity;
    auto* temp = new ArrayChunk[m_capacity];

    for (Size i = 0; i < m_used; ++i) {
      temp[i].value = m_data[i].value;
    }

    delete[] m_data;
    m_data = temp;
  }

  template<typename T>
  void Array<T>::Sort(const algorithms::Sort a_algorithm) {
    switch (a_algorithm) {
      case algorithms::Sort::DYNAMIC:
        dynamicSort();
        break;
      case algorithms::Sort::INSERTION_SORT:
        insertionSort();
        break;
      case algorithms::Sort::QUICK_SORT:
        quickSort(0, m_used - 1);
        break;
      case algorithms::Sort::MERGE_SORT:
        mergeSort();
        break;
      default:
        VERIFY(a_algorithm == algorithms::Sort::DYNAMIC)
        break;
    }
  }

  template<typename T>
  I64 Array<T>::Find(const T& a_element) const {
    if (m_used == 0)
      return -1;

    return m_sorted ? binarySearch(a_element, 0, m_used - 1) : frontBackSearch(a_element, 0, m_used - 1);
  }

  template<typename T>
  I64 Array<T>::Find(const T& a_element, const I64 a_from, const I64 a_to, const algorithms::Search a_algorithm) const {
    if (m_used == 0)
      return -1;

    switch (a_algorithm) {
      case algorithms::Search::BINARY_SEARCH:
        VERIFY(m_sorted)
        return binarySearch(a_element, a_from, a_to);
      case algorithms::Search::FRONT_BACK_SEARCH:
        return frontBackSearch(a_element, a_from, a_to);
      default:
        VERIFY(a_algorithm == algorithms::Search::BINARY_SEARCH)
        return -1;
    }
  }

  template<typename T>
  const T& Array<T>::Get(Size a_index) const {
    VERIFY(a_index < m_used)

    return m_data[a_index].value;
  }

  template<typename T>
  T& Array<T>::Get(Size a_index) {
    VERIFY(a_index < m_used)

    return m_data[a_index].value;
  }

  template<typename T>
  const T& Array<T>::GetFirst() const {
    return m_data[0].value;
  }

  template<typename T>
  T& Array<T>::GetFirst() {
    return m_data[0].value;
  }

  template<typename T>
  const T& Array<T>::GetLast() const {
    return m_data[m_used - 1].value;
  }

  template<typename T>
  T& Array<T>::GetLast() {
    return m_data[m_used - 1].value;
  }

  template<typename T>
  void Array<T>::GetNeighbors(const T& a_element, T*& a_left, T*& a_right) {
    I64 idx = Find(a_element);

    a_left = nullptr;
    a_right = nullptr;

    if (idx == -1)
      return;

    if (idx > 0)
      a_left = reinterpret_cast<T*>(m_data + idx - 1);

    if (idx < m_used)
      a_right = reinterpret_cast<T*>(m_data + idx);
  }

  template<typename T>
  Array<T> Array<T>::GetSubArray(const Size a_from, const Size a_to) const {
    VERIFY(a_from < a_to)
    VERIFY(a_from < m_used)
    VERIFY(a_to < m_used)


    Array result((a_to - a_from), m_sorted, m_growable);
    result.m_sorted = m_sorted;

    for (Size i = a_from; i < a_to; ++i) {
      result.m_data[result.m_used++] = m_data[i];
    }

    return result;
  }

  template<typename T>
  bool Array<T>::IsEqual(const Array<T>& a_other) const {
    if (m_used != a_other.m_used)
      return false;

    bool result = true;

    for (Size i = 0; i < m_used; ++i) {
      if (m_data[i].value != a_other.m_data[i].value) {
        result = false;
        break;
      }
    }

    return result;
  }

  template<typename T>
  bool Array<T>::IsEmpty() const {
    return (m_used == 0);
  }

  template<typename T>
  Size Array<T>::GetCapacity() const {
    return m_capacity;
  }

  template<typename T>
  Size Array<T>::GetSize() const {
    return m_used;
  }

  template<typename T>
  T* Array<T>::GetData() const {
    return m_data;
  }

  template<typename T>
  T& Array<T>::operator[](const Size a_index) {
    return Get(a_index);
  }

  template<typename T>
  const T& Array<T>::operator[](const Size a_index) const {
    return Get(a_index);
  }

  template<typename T>
  Array<T>& Array<T>::operator+=(const T& a_element) {
    Insert(a_element);
    return (*this);
  }

  template<typename T>
  Array<T>& Array<T>::operator-=(const T& a_element) {
    RemoveElement(a_element);
    return (*this);
  }

  template<typename T>
  bool Array<T>::operator==(const Array& a_other) const {
    return IsEqual(a_other);
  }

  template<typename T>
  bool Array<T>::operator!=(const Array& a_other) const {
    return (!IsEqual(a_other));
  }

  template<typename T>
  String Array<T>::ToString() const {
    String result = "Array(";

    for (int i = 0; i < m_used; ++i) {
      result += m_data[i].value;
      result += (i == m_used - 1) ? ")\n" : ", ";
    }

    return result;
  }

  /*********************************************************************************************************************
   *                                                      ARRAY                                                        *
   *                                                 PRIVATE METHODS                                                   *
   ********************************************************************************************************************/

  template<typename T>
  I64 Array<T>::binarySearch(const T& a_element, const I64 a_from, const I64 a_to) const {
    if constexpr (has_less_than<T> && has_bigger_than<T>) {
      if (a_from == a_to)
        return a_from;

      if (a_from > a_to)
        return -1;

      I64 pivot = (a_from + a_to) / 2;

      if (a_element < m_data[pivot].value) {
        return binarySearch(a_element, a_from, pivot - 1);
      } else if (a_element > m_data[pivot].value) {
        return binarySearch(a_element, pivot + 1, a_to);
      } else {
        return pivot;
      }
    } else {
      return frontBackSearch(a_element, a_from, a_to);
    }
  }

  template<typename T>
  I64 Array<T>::frontBackSearch(const T& a_element, I64 a_from, I64 a_to) const {
    while (a_from <= a_to) {
      if (m_data[a_from].value == a_element)
        return a_from;

      if (m_data[a_to].value == a_element)
        return a_to;

      a_from++;
      a_to--;
    }

    return -1;
  }

  template<typename T>
  void Array<T>::insertionSort() {
    if constexpr (has_bigger_than<T>) {
      for (int i = 1; i < m_used; ++i) {
        ArrayChunk temp = m_data[i];
        int j = i - 1;
        while (m_data[j].value > temp.value && j >= 0) {
          m_data[j + 1] = m_data[j];
          j--;
        }
        m_data[j + 1] = temp;
      }

      m_sorted = true;
    } else {
      VERIFY(has_bigger_than<T>)
    }
  }

  template<typename T>
  void Array<T>::quickSort(const I64 a_from, const I64 a_to) {
    if (m_used == 0)
      return;

    if (a_from >= a_to) {
      m_sorted = true;
      return;
    }

    const I64 k = partition(a_from, a_to);
    quickSort(a_from, k - 1);
    quickSort(k + 1, a_to);
  }

  template<typename T>
  void Array<T>::mergeSort() {
    ArrayChunk* temp = mergeSort(m_data, m_capacity, m_used);
    delete[] m_data;
    m_data = temp;
    m_sorted = true;
  }

  template<typename T>
  typename Array<T>::ArrayChunk* Array<T>::mergeSort(ArrayChunk* a_array, const I64 a_capacity, const I64 a_used) {
    if constexpr (has_less_equals_than<T>) {
      ArrayChunk* result;

      if (a_used <= 1) {
        result = new ArrayChunk[1];
        result[0] = a_array[0];
        return result;
      }

      const I64 size1 = a_used / 2;
      const I64 size2 = a_used - size1;

      auto* array1 = mergeSort(a_array, size1, size1);
      auto* array2 = mergeSort(a_array + size1, size2, size2);

      result = new ArrayChunk[a_capacity];

      Size j = 0, k = 0;
      for (Size i = 0; i < a_used; ++i) {
        if ((j < size1) && (k == size2 || array1[j].value <= array2[k].value)) {
          result[i] = array1[j];
          j++;
        } else {
          result[i] = array2[k];
          k++;
        }
      }

      delete[] array1;
      delete[] array2;

      return result;
    } else {
      VERIFY(has_less_equals_than<T>)
      return m_data;
    }
  }

  template<typename T>
  void Array<T>::dynamicSort() {
    if constexpr (has_less_equals_than<T> && has_bigger_than<T>) {
      // TODO: improve also using insertion sort when mergesort array is small
      if (m_used > 64) {
        mergeSort();
      } else {
        insertionSort();
      }
    }
  }

  template<typename T>
  I64 Array<T>::partition(const I64 a_from, const I64 a_to) {
    if constexpr (has_less_equals_than<T>) {
      const T& pivot = m_data[a_to].value;

      I64 i = a_from - 1;

      for (I64 j = a_from; j < a_to; ++j) {
        if (m_data[j].value <= pivot) {
          Swap(i + 1, j);
          i++;
        }
      }

      Swap(i + 1, a_to);
      i++;

      return i;
    } else {
      VERIFY(has_less_equals_than<T>)
      return -1;
    }
  }
}

#endif // NTL_ARRAY_HPP
