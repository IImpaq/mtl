/**
 * @file String.hpp
 * @author Marcus Gugacs
 * @date 02/08/2024
 * @copyright Copyright (c) 2022-2024 Marcus Gugacs. All rights reserved.
 */

#ifndef NTL_STRING_HPP
#define NTL_STRING_HPP

#include <algorithm>
#include <ostream>

#include "core/Assert.hpp"
#include "data/Size.hpp"
#include "utils/Hash.hpp"

#define DEFAULT_STRING_SIZE 1024

namespace ntl {
  /**
   * @brief String class representing a collection of characters.
   */
  class String {
  public:
    /**
     * @brief Iterator class to simplify iteration over string.
     */
    class Iterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = char;
      using pointer = char*;
      using reference = char&;

    private:
      pointer m_ptr;

    public:
      /**
       * @brief Constructs a new iterator
       * @param a_ptr a pointer
       */
      Iterator(pointer a_ptr);

      /**
       * @brief Overloading reference operator.
       * @return the reference to the value of the current iteration
       */
      char& operator*() const;

      /**
       * @brief Overloading pointer operator.
       * @return the pointer to the value of the current iteration
       */
      char* operator->() const;

      /**
       * @brief Overloading increment operator.
       * @return the reference to the next iterator
       */
      Iterator& operator++();

      /**
       * @brief Overloading increment operator.
       * @return the next iterator
       */
      const Iterator operator++(int);

      /**
       * @brief Overloading equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors are equivalent
       */
      friend bool operator==(const Iterator& a_first, const Iterator& a_second);

      /**
       * @brief Overloading anti equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors aren't equivalent
       */
      friend bool operator!=(const Iterator& a_first, const Iterator& a_second);
    };

  private:
    Size m_capacity, m_used;
    char* m_data;

  public:
    /**
     * @brief Default Constructor.
     *
     * @details Runtime: O(1)
     */
    String();

    /**
     * @brief Creates a new String object using a single character.
     *
     * @details Runtime: O(1)
     *
     * @param a_char a character
     */
    String(char a_char);

    /**
     * @brief Creates a String object using a given c-string.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @param a_string a c-string
     */
    String(const char* a_string);

    /**
     * @brief Default Destructor.
     *
     * @details Runtime: O(1)
     *
     */
    ~String();

    /**
     * @brief Copy Constructor.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @param a_other a string
     */
    String(const String& a_other);

    /**
     * @brief Move Constructor.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @param a_other a string
     */
    String(String&& a_other) noexcept;

    /**
     * @brief Appends another string to the current string.
     *
     * @details Runtime: O(n), where n is the length of the string getting appended
     *
     * @param a_other the other string
     * @return the reference to the current string
     */
    String& Append(const String& a_other);

    /**
     * @brief Appends a c-string to the current string.
     *
     * @details Runtime: O(n), where n is the length of the c-string getting appended
     *
     * @param a_other the c-string
     * @return the reference to the current string
     */
    String& Append(const char* a_other);

    /**
     * @brief Appends a character to the current string.
     *
     * @details Runtime: O(1)
     *
     * @param a_other the character
     * @return the reference to the current string
     */
    String& Append(char a_other);

    /**
     * @brief Appends an integer to the current string.
     *
     * @details Runtime: O(n), where n is the number of digits of the integer
     *
     * @param a_other the integer
     * @return the reference to the current string
     */
    String& Append(int a_other);

    /**
     * @brief Appends a size to the current string.
     *
     * @details Runtime: O(n), where n is the number of digits of the size
     *
     * @param a_other the size
     * @return the reference to the current string
     */
    String& Append(Size a_other);

    /**
     * @brief Appends a double to the current string.
     *
     * @details Runtime: O(n), where n is the number of digits of the double
     *
     * @param a_other the double
     * @return the reference to the current string
     */
    String& Append(double a_other);

    /**
     * @brief Appends a float to the current string.
     *
     * @details Runtime: O(n), where n is the number of digits of the float
     *
     * @param a_other the float
     * @return the reference to the current string
     */
    String& Append(float a_other);

    /**
     * @brief Appends a boolean to the current string.
     *
     * @details Runtime: O(4), because either true or false have 4 characters
     *
     * @param a_other the boolean
     * @return the reference to the current string
     */
    String& Append(bool a_other);

    /**
     * @brief Removes a character from the current string.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @param a_other the character to remove
     * @return the reference to the current string
     */
    String& Remove(char a_other);

    /**
     * @brief Clears the content of the string.
     *
     * @details Runtime: O(1)
     */
    String& Clear();

    /**
     * @brief Resizes the string to the given capacity.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @param a_capacity the capacity to resize to
     */
    void Resize(Size a_capacity);

    /**
     * @brief Finds the first occurrence of a given char.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @param a_char a char
     * @return the index of the first occurrence
     */
    [[nodiscard]] Size Find(char a_char) const;

    /**
     * @brief Replaces a given string with another string.
     *
     * @details Runtime: O(n*m), where n is the length of the string
     * and m is the length of the old sequence string that will be replaced
     *
     * @param a_old an old string to replace
     * @param a_new a new string to replace the old one with
     * @return the reference to the current string object
     */
    String& Replace(const String& a_old, const String& a_new);

    /**
     * @brief Replaces a given char with another one.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @param a_old an old char to replace
     * @param a_new a new char to replace the old one with
     * @return the reference to the current string object
     */
    String& Replace(char a_old, char a_new);

    /**
     * @brief Gets a copy of the string in lowercase.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @return the lowercase string object
     */
    String& ToLowerCase();

    /**
     * @brief Converts the string to be uppercase.
     *
     * @details Runtime: O(n), where n is the length of the string
     *
     * @return the reference to the current string object
     */
    String& ToUpperCase();

    /**
     * @brief Gets the hash of the current string.
     *
     * @details Runtime: O(1)
     *
     * @return the generated hash
     */
    [[nodiscard]] Size GetHash() const;

    /**
     * @brief Gets the character at the given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the character
     * @return the character itself
     */
    [[nodiscard]] const char& Get(Size a_index) const;

    /**
     * @brief Gets the character at the given index.
     *
     * @details Runtime: O(1)
     *
     * @param a_index the index of the character
     * @return the character itself
     */
    char& Get(Size a_index);

    /**
     * @brief Checks if the string is equal to another string.
     *
     * @details Runtime: O(1)
     *
     * @param a_other the other string to compare with
     * @return if the strings are equal
     */
    [[nodiscard]] bool IsEqual(const String& a_other) const;

    /**
     * @brief Checks if the string is equal to another c-string.
     *
     * @details Runtime: O(n), where n is the length of the string.
     *
     * @param a_other the other string to compare with
     * @return if the strings are equal
     */
    bool IsEqual(const char* a_other) const;

    /**
     * @brief Gets the content of the string as a c-string.
     *
     * @details Runtime: O(1)
     *
     * @return the content as a c-string
     */
    [[nodiscard]] const char* GetCString() const;

    /**
     * @brief Gets the length of the string (without the null terminator).
     *
     * @details Runtime: O(1)
     *
     * @return the length of the string
     */
    [[nodiscard]] Size GetLength() const;

    /**
     * @brief Gets the size of the string (including the null terminator).
     *
     * @details Runtime: O(1)
     *
     * @return the size of the string
     */
    [[nodiscard]] Size GetSize() const;

    /**
     * @brief Gets the capacity of the string.
     *
     * @details Runtime: O(1)
     *
     * @return the maximum capacity
     */
    [[nodiscard]] Size GetCapacity() const;

    /**
     * @brief Gets if the string is empty.
     *
     * @details Runtime: O(1)
     *
     * @return if the string is empty
     */
    [[nodiscard]] bool IsEmpty() const;

    /**
     * @brief Swaps two strings with each other.
     *
     * @details Runtime: O(1)
     *
     * @param a_left the first string
     * @param a_right the second string
     */
    friend void swap(String& a_left, String& a_right) noexcept;

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

    /**
     * @brief Overloading assignment operator.
     * @param a_other a string
     * @return the reference to the current string object
     */
    String& operator=(const String& a_other);

    /**
     * @brief Overloading assignment operator.
     * @param a_string a c-string
     * @return the reference to the current string object
     */
    String& operator=(const char* a_string);

    /**
     * @brief Overloading subscript operator.
     * @param a_index a index
     * @return the char at a given index
     */
    const char& operator[](Size a_index) const;

    /**
     * @brief Overloading subscript operator.
     * @param a_index a index
     * @return the reference to the char at a given index
     */
    char& operator[](Size a_index);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the string to add
     * @return the reference of the current string object
     */
    String& operator+=(const String& a_other);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the c-string to add
     * @return the reference of the current string object
     */
    String& operator+=(const char* a_other);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the character to add
     * @return the reference of the current string object
     */
    String& operator+=(char a_other);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the integer to add
     * @return the reference of the current string object
     */
    String& operator+=(int a_other);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the size_t to add
     * @return the reference of the current string object
     */
    String& operator+=(Size a_other);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the double to add
     * @return the reference of the current string object
     */
    String& operator+=(double a_other);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the float to add
     * @return the reference of the current string object
     */
    String& operator+=(float a_other);

    /**
     * @brief Overloading addition assignment operator.
     * @param a_other the bool to add
     * @return the reference of the current string object
     */
    String& operator+=(bool a_other);

    /**
     * @brief Overloading equivalence operator.
     * @param a_other a string to compare with
     * @return if both strings are equivalent
     */
    bool operator==(const String& a_other) const;

    /**
     * @brief Overloading equivalence operator.
     * @param a_other a c-string to compare with
     * @return if both strings are equivalent
     */
    bool operator==(const char* a_other) const;

    /**
     * @brief Overloading anti equivalence operator.
     * @param a_other a string to compare with
     * @return if both strings aren't equivalent
     */
    bool operator!=(const String& a_other) const;

    /**
     * @brief Overloading anti equivalence operator.
     * @param a_other a c-string to compare with
     * @return if both strings aren't equivalent
     */
    bool operator!=(const char* a_other) const;

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the string to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, const String& a_right);

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the c-string to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, const char* a_right);

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the cchar to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, char a_right);

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the integer to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, int a_right);

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the size_t to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, Size a_right);

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the double to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, double a_right);

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the float to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, float a_right);

    /**
     * @brief Overloading addition operator.
     * @param a_left the string to append to
     * @param a_right the bool to append
     * @return the concatenated vector object
     */
    friend String operator+(const String& a_left, bool a_right);

    /**
     * @brief Overloading the left shift operator.
     * @param a_stream the ostream
     * @param a_string the string
     * @return the combined ostream
     */
    friend std::ostream& operator<<(std::ostream& a_stream, const String& a_string);
  };
} // namespace ntl

#endif // NTL_STRING_HPP
