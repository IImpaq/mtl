/**
* @file Bitset.hpp
* @author Marcus Gugacs
* @date 02/08/2024
* @copyright Copyright (c) 2023-2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_BITSET_HPP
#define NTL_BITSET_HPP

#include "core/Assert.hpp"
#include "data/Byte.hpp"
#include "data/String.hpp"
#include "data/Size.hpp"

namespace ntl {
  /**
   * @brief Constructs a new bitset object.
   */
  template<Size capacity = 1024>
  class Bitset {
  private:
    Byte* m_bits;
    Size m_capacity,
        m_size;

  public:
    /**
     * @brief Constructs a new bitset with the given parameters.
     *
     * @details Runtime: O(1)
     */
    Bitset();

    /**
     * @brief Destructs the bitset.
     *
     * @details Runtime: O(1)
     */
    ~Bitset();

    /**
     * @brief Copy constructor for bitset.
     *
     * @details Runtime: O(1)
     *
     * @param a_other the bitset to be copied
     */
    Bitset(const Bitset& a_other);

    /**
     * @brief Copy assignment operator for bitset.
     *
     * @details Runtime: O(1)
     *
     * @param a_right the other bitset whose contents are to be assigned
     * @return a reference to the modified bitset
     */
    Bitset& operator=(const Bitset& a_right);

    /**
     * @brief Move constructor for bitset.
     *
     * @details Runtime: O(1)
     *
     * @param a_other the other bitset whose contents are to be moved
     */
    Bitset(Bitset&& a_other) noexcept;

    /**
     * @brief Move assignment operator for bitset.
     *
     * @details Runtime: O(1)
     *
     * @param a_right the pther bitset whose contents are to be moved
     * @return a reference to the modified bitset
     */
    Bitset& operator=(Bitset&& a_right) noexcept;

    /**
     * @brief Sets the bit at a given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the bit to set
     */
    void Set(Size a_index);

    /**
     * @brief Resets the bit at a given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the bit to reset
     */
    void Reset(Size a_index);

    /**
     * @brief Resets all bits in the set.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     */
    void Reset();

    /**
     * @brief Flips the bit at a given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the bit to flip
     */
    void Flip(Size a_index);

    /**
     * @brief Gets the bit at a given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the bit to get
     * @return the reference to the bit
     */
    Byte& Get(Size a_index);

    /**
     * @brief Gets the bit at a given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the bit to get
     * @return the reference to the bit
     */
    [[nodiscard]] const Byte& Get(Size a_index) const;

    /**
     * @brief Gets the size of the bitset.
     *
     * @details Runtime: O(1)
     *
     * @return the size of the bitset
     */
    [[nodiscard]] Size GetSize() const;

    /**
     * @brief Gets the capacity of the bitset.
     *
     * @details Runtime: O(1)
     *
     * @return the capacity of the bitset
     */
    [[nodiscard]] Size GetCapacity() const;

    /**
     * @brief Gets the bit count of the bitset.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @return the counted bits
     */
    [[nodiscard]] Size GetCount() const;

    /**
     * @brief Gets if the bit at a given index is set.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index to check if set
     * @return if the bit is set
     */
    [[nodiscard]] bool IsSet(Size a_index) const;

    /**
     * @brief Gets if no bits are set in the bitset.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @return if no bits are set
     */
    [[nodiscard]] bool IsNone() const;

    /**
     * @brief Gets if any bit is set in the bitset.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @return if any bit is set
     */
    [[nodiscard]] bool IsAny() const;

    /**
     * @brief Checks if the bitset is equal to another bitset.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @param a_other the other bitset to compare with
     * @return if the bitsets are equal
     */
    [[nodiscard]] bool IsEqual(const Bitset& a_other) const;

    /**
     * @brief Gets the bit at a given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the bit to get
     * @return the reference to the bit
     */
    Byte& operator[](Size a_index);

    /**
     * @brief Gets the bit at a given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the bit to get
     * @return the reference to the bit
     */
    const Byte& operator[](Size a_index) const;

    /**
     * @brief Overloading bitwise and comparison operator.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @param a_other the other bitset to compare with
     * @return the resulting bitset
     */
    Bitset operator&(const Bitset& a_other) const;

    /**
     * @brief Overloading equivalence operator.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @param a_other the bitset to compare with
     * @return if both bitsets are equivalent
     */
    bool operator==(const Bitset& a_other) const;

    /**
     * @brief Overloading anti equivalence operator.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @param a_other the bitset to compare with
     * @return if both bitsets aren't equivalent
     */
    bool operator!=(const Bitset& a_other) const;

    /**
     * @brief Converts the current bitset to a string.
     *
     * @details Runtime: O(n), where n is the size of the bitset
     *
     * @return the bitset as a string
     */
    [[nodiscard]] String ToString() const;
  };

  /*********************************************************************************************************************
   *                                                      BITSET                                                       *
   *                                           GLOBAL OVERLOADED OPERATORS                                             *
   ********************************************************************************************************************/

  /**
   * @brief Overloading the left shift operator.
   * @param a_stream the ostream
   * @param a_bitset the bitset
   * @return the combined ostream
   */
  template<Size size>
  std::ostream& operator<<(std::ostream& a_stream, const Bitset<size>& a_bitset) {
    return (a_stream << a_bitset.ToString());
  }

  /*********************************************************************************************************************
   *                                                      BITSET                                                       *
   *                                                  PUBLIC METHODS                                                   *
   ********************************************************************************************************************/

  template<Size size>
  Bitset<size>::Bitset()
    : m_capacity{size + 1}, m_size{size} {
    m_bits = new Byte[m_capacity];
    Reset();
  }

  template<Size size>
  Bitset<size>::~Bitset() {
    if (m_bits) {
      delete[] m_bits;
      m_bits = nullptr;
    }
  }

  template<Size size>
  Bitset<size>::Bitset(const Bitset& a_other)
    : m_capacity{a_other.m_capacity}, m_size{a_other.m_size} {
    if (m_capacity > 0) {
      m_bits = new Byte[m_capacity];
      memcpy(m_bits, a_other.m_bits, m_capacity);
    }
  }

  template<Size size>
  Bitset<size>& Bitset<size>::operator=(const Bitset& a_right) {
    VERIFY(this != &a_right)

    m_size = a_right.m_size;
    m_capacity = a_right.m_capacity;
    m_bits = new Byte[m_capacity];
    memcpy(m_bits, a_right.m_bits, m_capacity);

    return *this;
  }

  template<Size size>
  Bitset<size>::Bitset(Bitset&& a_other) noexcept {
    VERIFY(this != &a_other)

    m_size = a_other.m_size;
    m_capacity = a_other.m_capacity;
    m_bits = a_other.m_bits;

    a_other.m_size = 0;
    a_other.m_capacity = 0;
    a_other.m_bits = nullptr;
  }

  template<Size size>
  Bitset<size>& Bitset<size>::operator=(Bitset&& a_right) noexcept {
    VERIFY(this != &a_right)

    m_size = a_right.m_size;
    m_capacity = a_right.m_capacity;
    m_bits = a_right.m_bits;

    a_right.m_size = 0;
    a_right.m_capacity = 0;
    a_right.m_bits = nullptr;

    return *this;
  }

  template<Size size>
  void Bitset<size>::Set(const Size a_index) {
    m_bits[a_index] = '1';
  }

  template<Size size>
  void Bitset<size>::Reset(const Size a_index) {
    m_bits[a_index] = '0';
  }

  template<Size size>
  void Bitset<size>::Reset() {
    memset(m_bits, '0', m_size);
  }

  template<Size size>
  void Bitset<size>::Flip(const Size a_index) {
    m_bits[a_index] = (m_bits[a_index] == '0') ? '1' : '0';
  }

  template<Size size>
  Byte& Bitset<size>::Get(const Size a_index) {
    return m_bits[a_index];
  }

  template<Size size>
  const Byte& Bitset<size>::Get(const Size a_index) const {
    return m_bits[a_index];
  }

  template<Size size>
  Size Bitset<size>::GetSize() const {
    return m_size;
  }

  template<Size size>
  Size Bitset<size>::GetCapacity() const {
    return m_capacity;
  }

  template<Size size>
  bool Bitset<size>::IsSet(const Size a_index) const {
    return (m_bits[a_index] == '1');
  }

  template<Size size>
  Size Bitset<size>::GetCount() const {
    Size result = 0;
    for (Size i = 0; i < m_size; ++i) {
      if (m_bits[i] == '1')
        result++;
    }
    return result;
  }

  template<Size size>
  bool Bitset<size>::IsNone() const {
    for (Size i = 0; i < m_size; ++i) {
      if (m_bits[i] == '1')
        return false;
    }
    return true;
  }

  template<Size size>
  bool Bitset<size>::IsAny() const {
    for (Size i = 0; i < m_size; ++i) {
      if (m_bits[i] == '1')
        return true;
    }
    return false;
  }

  template<Size size>
  bool Bitset<size>::IsEqual(const Bitset& a_other) const {
    if (m_size != a_other.m_size)
      return false;

    bool result = true;

    for (Size i = 0; i < m_size; ++i) {
      if (m_bits[i] != a_other.m_bits[i]) {
        result = false;
        break;
      }
    }

    return result;
  }

  template<Size size>
  Byte& Bitset<size>::operator[](const Size a_index) {
    return Get(a_index);
  }

  template<Size size>
  const Byte& Bitset<size>::operator[](const Size a_index) const {
    return Get(a_index);
  }

  template<Size size>
  Bitset<size> Bitset<size>::operator&(const Bitset& a_other) const {
    VERIFY(m_size == a_other.m_size && "Both Bitsets must have the same size")

    Bitset result;
    for (Size i = 0; i < result.m_size; ++i) {
      result.m_bits[i] = (m_bits[i] & a_other.m_bits[i]);
    }

    return result;
  }

  template<Size size>
  bool Bitset<size>::operator==(const Bitset& a_other) const {
    return IsEqual(a_other);
  }

  template<Size size>
  bool Bitset<size>::operator!=(const Bitset& a_other) const {
    return (!IsEqual(a_other));
  }

  template<Size size>
  String Bitset<size>::ToString() const {
    String result = "Bitset(";

    for (Size i = 0; i < m_size; ++i) {
      result += m_bits[i] - '0';
      if (i == m_size - 1)
        result += ")\n";
    }

    return result;
  }
}

#endif // NTL_BITSET_HPP
