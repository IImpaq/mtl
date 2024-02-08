/**
 * @file String.hpp
 * @author Marcus Gugacs
 * @date 02/08/2024
 * @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
 */

#include "String.hpp"

namespace ntl {
  /*********************************************************************************************************************
   *                                                    ITERATOR                                                       *
   *                                                   CONSTRUCTOR                                                     *
   ********************************************************************************************************************/

  String::Iterator::Iterator(pointer a_ptr)
    : m_ptr(a_ptr) {
    // Empty
  }

  /*********************************************************************************************************************
   *                                                    ITERATOR                                                       *
   *                                              OVERLOADED OPERATORS                                                 *
   ********************************************************************************************************************/

  char& String::Iterator::operator*() const { return (*m_ptr); }

  char* String::Iterator::operator->() const { return m_ptr; }

  String::Iterator& String::Iterator::operator++() {
    m_ptr++;
    return *this;
  }

  const String::Iterator String::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const String::Iterator& a_first, const String::Iterator& a_second) {
    return a_first.m_ptr == a_second.m_ptr;
  }

  bool operator!=(const String::Iterator& a_first, const String::Iterator& a_second) { return !(a_first == a_second); }

  /*********************************************************************************************************************
   *                                                     STRING                                                        *
   *                                                  CONSTRUCTORS                                                     *
   ********************************************************************************************************************/

  String::String()
    : m_capacity{DEFAULT_STRING_SIZE}, m_used{0}, m_data{new char[m_capacity + 1]} {
    m_data[m_used] = '\0';
  }

  String::String(char a_char)
    : m_capacity{DEFAULT_STRING_SIZE}, m_used{1}, m_data{new char[m_capacity + 1]} {
    m_data[m_used - 1] = a_char;
    m_data[m_used] = '\0';
  }

  String::String(const char* a_string)
    : m_used{std::strlen(a_string)}, m_data{new char[(m_used * 2) + 1]} {
    VERIFY(a_string != nullptr)

    m_capacity = m_used * 2;
    std::copy_n(a_string, m_used, m_data);
    m_data[m_used] = '\0';
  }

  String::~String() { delete[] m_data; }

  String::String(const String& a_other)
    : m_capacity{a_other.m_used * 2}, m_used{a_other.m_used}, m_data{new char[m_capacity + 1]} {
    std::copy_n(a_other.m_data, m_used, m_data);
    m_data[m_used] = '\0';
  }

  String::String(String&& a_other) noexcept : String() { swap(*this, a_other); }

  /*********************************************************************************************************************
   *                                                     STRING                                                        *
   *                                                 PUBLIC METHODS                                                    *
   ********************************************************************************************************************/

  String& String::Append(const String& a_other) {
    const Size total_len = m_used + a_other.m_used;

    if (total_len >= m_capacity) {
      Resize(total_len * 2);
    }

    for (Size i = 0; i < a_other.m_used; ++i) {
      m_data[m_used + i] = a_other.m_data[i];
    }

    m_used = total_len;
    m_data[m_used] = '\0';

    return *this;
  }

  String& String::Append(const char* a_other) {
    const Size other_len = std::strlen(a_other);
    const Size total_len = m_used + other_len;

    if (total_len >= m_capacity) {
      Resize(total_len * 2);
    }

    for (Size i = 0; i < other_len; ++i) {
      m_data[m_used + i] = a_other[i];
    }

    m_used = total_len;
    m_data[m_used] = '\0';
    return *this;
  }

  String& String::Append(const char a_other) {
    const Size total_len = m_used + 1;

    if (total_len >= m_capacity) {
      Resize(total_len * 2);
    }

    m_data[m_used] = a_other;

    m_used = total_len;
    m_data[m_used] = '\0';
    return *this;
  }

  String& String::Append(const int a_other) { return Append(std::to_string(a_other).c_str()); }

  String& String::Append(const Size a_other) { return Append(std::to_string(a_other).c_str()); }

  String& String::Append(const double a_other) { return Append(std::to_string(a_other).c_str()); }

  String& String::Append(const float a_other) { return Append(std::to_string(a_other).c_str()); }

  String& String::Append(const bool a_other) { return Append(a_other ? "true" : "false"); }

  String& String::Remove(const char a_other) { return Replace(a_other, '\0'); }

  String& String::Clear() {
    delete[] m_data;
    m_used = 0;
    m_data = new char[m_capacity + 1];
    m_data[m_used] = '\0';

    return *this;
  }

  void String::Resize(const Size a_capacity) {
    VERIFY(a_capacity >= (m_used + 1))
    VERIFY(a_capacity > m_capacity)

    m_capacity = a_capacity;
    auto* temp = new char[m_capacity];

    for (Size i = 0; i < m_used; ++i) {
      temp[i] = m_data[i];
    }
    temp[m_used] = '\0';

    delete[] m_data;
    m_data = temp;
  }

  Size String::Find(const char a_char) const {
    Size index = 0;

    while (index < m_used && m_data[index] != a_char) {
      index++;
    }

    return index >= m_used ? -1 : index;
  }

  String& String::Replace(const String& a_old, const String& a_new) {
    VERIFY(!a_old.IsEmpty())

    Size seq_idx = -1;

    for (Size i = 0; i < m_used; ++i) {
      if (m_data[i] != a_old[0])
        continue;

      bool found = true;

      for (Size j = 1; j < a_old.m_used; ++j) {
        if (m_data[i + j] != a_old[j]) {
          found = false;
          break;
        }
      }

      if (found) {
        seq_idx = i;
        break;
      }
    }

    if (seq_idx == -1)
      return (*this);

    if (a_old.m_used == a_new.m_used) {
      for (Size new_idx = 0; new_idx < a_new.m_used; ++new_idx) {
        m_data[seq_idx + new_idx] = a_new[new_idx];
      }
    } else {
      // TODO: improve replacing of bigger string
      const Size new_length = m_used - (a_old.m_used - a_new.m_used);

      if (new_length <= m_capacity) {
        Resize(m_capacity * 2);
      }

      auto* temp = new char[m_capacity + 1];
      for (Size i = 0; i < seq_idx; ++i) {
        temp[i] = m_data[i];
      }

      for (Size i = 0; i < a_new.m_used; ++i) {
        temp[seq_idx + i] = a_new.m_data[i];
      }

      for (Size i = seq_idx; i < m_used; ++i) {
        temp[a_new.m_used + i] = m_data[a_old.m_used + i];
      }

      delete[] m_data;
      m_data = temp;

      m_used = new_length;
      m_data[m_used] = '\0';
    }

    return (*this);
  }

  String& String::Replace(const char a_old, const char a_new) {
    if (a_new == '\0') {
      Size i = 0;
      for (; i < m_used; ++i) {
        if (m_data[i] == a_old)
          break;
      }
      for (; i < m_used; ++i) {
        m_data[i] = m_data[i + 1];
      }
      m_used--;
      m_data[m_used] = '\0';
    } else {
      for (Size i = 0; i < m_used; ++i) {
        if (m_data[i] != a_old)
          continue;

        m_data[i] = a_new;
      }
    }

    return (*this);
  }

  String& String::ToLowerCase() {
    std::transform(begin(), end(), m_data, [](const unsigned char a_char) { return std::tolower(a_char); });
    return (*this);
  }

  String& String::ToUpperCase() {
    std::transform(begin(), end(), m_data, [](const unsigned char a_char) { return std::toupper(a_char); });
    return (*this);
  }

  Size String::GetHash() const {
    Size hash{0};
    hash::Combine(hash, *m_data, m_used);
    return hash;
  }

  const char& String::Get(const Size a_index) const {
    VERIFY(a_index < m_used)
    return m_data[a_index];
  }

  char& String::Get(const Size a_index) { return m_data[a_index]; }

  bool String::IsEqual(const String& a_other) const {
    if (m_used != a_other.m_used)
      return false;

    for (Size i = 0; i < m_used; ++i) {
      if (m_data[i] != a_other.m_data[i])
        return false;
    }

    return true;
  }

  bool String::IsEqual(const char* a_other) const {
    VERIFY(a_other != nullptr)
    return (strcmp(m_data, a_other) == 0);
  }

  const char* String::GetCString() const { return m_data; }

  Size String::GetLength() const { return m_used; }

  Size String::GetSize() const { return m_used; }

  Size String::GetCapacity() const { return m_capacity; }

  bool String::IsEmpty() const { return m_used == 0; }

  void swap(String& a_left, String& a_right) noexcept {
    std::swap(a_left.m_capacity, a_right.m_capacity);
    std::swap(a_left.m_used, a_right.m_used);
    std::swap(a_left.m_data, a_right.m_data);
  }

  String::Iterator String::begin() { return {m_data}; }

  String::Iterator String::end() { return {m_data + m_used}; }

  /*********************************************************************************************************************
   *                                                     STRING                                                        *
   *                                              OVERLOADED OPERATORS                                                 *
   ********************************************************************************************************************/

  String& String::operator=(const String& a_other) {
    m_used = a_other.m_used;
    m_capacity = a_other.m_capacity;
    m_data = new char[m_capacity + 1];

    std::copy_n(a_other.m_data, m_used, m_data);

    m_data[m_used] = '\0';

    return (*this);
  }

  String& String::operator=(const char* a_string) {
    VERIFY(a_string != nullptr)

    const Size new_length = std::strlen(a_string);

    if (new_length >= m_capacity) {
      Resize(new_length * 2);
    }

    std::copy_n(a_string, new_length, m_data);

    m_used = new_length;
    m_data[m_used] = '\0';

    return (*this);
  }

  const char& String::operator[](const Size a_index) const { return Get(a_index); }

  char& String::operator[](const Size a_index) { return Get(a_index); }

  bool String::operator==(const String& a_other) const { return IsEqual(a_other); }

  bool String::operator==(const char* a_other) const { return IsEqual(a_other); }

  bool String::operator!=(const String& a_other) const { return (!((*this) == a_other)); }

  bool String::operator!=(const char* a_other) const {
    VERIFY(a_other != nullptr)
    return (!((*this) == a_other));
  }

  String& String::operator+=(const String& a_other) { return Append(a_other); }

  String& String::operator+=(const char* a_other) { return Append(a_other); }

  String& String::operator+=(const char a_other) { return Append(a_other); }

  String& String::operator+=(const int a_other) { return Append(a_other); }

  String& String::operator+=(const Size a_other) { return Append(a_other); }

  String& String::operator+=(const double a_other) { return Append(a_other); }

  String& String::operator+=(const float a_other) { return Append(a_other); }

  String& String::operator+=(const bool a_other) { return Append(a_other); }

  String operator+(const String& a_left, const String& a_right) {
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  String operator+(const String& a_left, const char* a_right) {
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  String operator+(const String& a_left, const char a_right) {
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  String operator+(const String& a_left, const int a_right) {
    /*auto size = static_cast<int>(trunc(log10(a_right)) + 1);
    char* c_str = new char[size];
    std::to_chars(c_str, c_str + size, a_right);*/
    // TODO: use to_chars in the future when it's working with floating point numbers
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  String operator+(const String& a_left, const Size a_right) {
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  String operator+(const String& a_left, const double a_right) {
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  String operator+(const String& a_left, const float a_right) {
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  String operator+(const String& a_left, const bool a_right) {
    String result{};
    result.Append(a_left);
    result.Append(a_right);

    return result;
  }

  std::ostream& operator<<(std::ostream& a_stream, const String& a_string) {
    a_stream << a_string.m_data;
    return a_stream;
  }

  /*********************************************************************************************************************
   *                                                     STRING                                                        *
   *                                                 PRIVATE METHODS                                                   *
   ********************************************************************************************************************/
} // namespace ntl
