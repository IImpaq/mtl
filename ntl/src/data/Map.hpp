/**
* @file Map.hpp
* @author Marcus Gugacs
* @date 10/31/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_MAP_HPP
#define NTL_MAP_HPP

#include "core/Algorithms.hpp"
#include "data/Bool.hpp"
#include "data/Integer.hpp"
#include "data/Float.hpp"
#include "data/Pair.hpp"
#include "data/Size.hpp"
#include "data/String.hpp"

namespace ntl {
  /**
   * @brief Constructs a new map object.
   * @tparam T the type of elements to store
   */
  template <typename KeyType, typename ValueType>
  class Map {
  private:
    /**
     * @brief Represents a single entry in the map.
     */
    struct Entry {
      KeyType key;
      ValueType value;
      Bool used;
    };

  public:
    /**
     * @brief Iterator class to simplify iteration over map.
     */
    class Iterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = Pair<KeyType, ValueType>;
      using pointer = value_type*;
      using reference = value_type&;

    private:
      Entry* m_ptr;
      mutable value_type m_temp;

    public:
      /**
       * @brief Constructs a new iterator
       * @param a_ptr a pointer
       */
      Iterator(Entry* a_ptr) : m_ptr(a_ptr) {}

      /**
       * @brief Overloading reference operator.
       * @return the reference to the value of the current iteration
       */
      reference operator*() const {
        m_temp = m_ptr->key, m_ptr->value;
        return m_temp;
      }

      /**
       * @brief Overloading pointer operator.
       * @return the pointer to the value of the current iteration
       */
      pointer operator->() {
        m_temp = {m_ptr->key, m_ptr->value};
        return &m_temp;
      }

      /**
       * @brief Overloading increment operator.
       * @return the reference to the next iterator
       */
      Iterator& operator++() {
        do {
          m_ptr++; // always move to next item
        } while(m_ptr->used == false);
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
       * @brief Overloading equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors are equivalent
       */
      friend Bool operator==(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr == a_second.m_ptr;
      }

      /**
       * @brief Overloading anti equivalence operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors aren't equivalent
       */
      friend Bool operator!=(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr != a_second.m_ptr;
      }

      /**
       * @brief Overloading anti greater-than operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors aren't equivalent
       */
      friend Bool operator>(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr > a_second.m_ptr;
      }

      /**
       * @brief Overloading anti less-than operator.
       * @param a_first the iterator to compare
       * @param a_second the iterator to compare with
       * @return if both vectors aren't equivalent
       */
      friend Bool operator<(const Iterator& a_first, const Iterator& a_second) {
        return a_first.m_ptr < a_second.m_ptr;
      }
    };

  private:
    Entry* m_entries;
    algorithms::Hash m_algorithm;
    Size m_capacity,
         m_used;
    Float m_grow_factor;
    Bool m_growable;

  public:
    /**
     * @brief Constructs a new map with the given parameters.
     *
     * The default capacity of the array is 1024 with auto sorting enabled
     * and automatic resizing disabled.
     *
     * @param a_capacity the maximum capacity
     * @param a_algorithm the hashing algorithm to use
     * @param a_grow_factor the factor of the capacity when to grow the map
     * @param a_growable if the map is growable (dynamic) or static
     */
    Map(Size a_capacity = 1024, algorithms::Hash a_algorithm = algorithms::Hash::FNV1a,
        Float a_grow_factor = 0.7, Bool a_growable = true);

    /**
     * @brief Constructs a new map from another map with double its used size as capacity.
     *
     * @details Runtime: O(n), where n is the used size of the passed map.
     *
     * @param a_other the other map
     */
    Map(const Map<KeyType, ValueType>& a_other);

    /**
     * @brief Constructs a new map from another map with a given capacity.
     *
     * @details Runtime: O(n), where n is the used size of the passed map.
     *
     * @param a_other the other map
     * @param a_capacity the maximum capacity
     */
    Map(const Map<KeyType, ValueType>& a_other, Size a_capacity);

    /**
     * @brief Destructs the map.
     */
    ~Map();

    /**
     * @brief Gets the value at the given key or creates the entry.
     *
     * @details Runtime: O(n), where n is the used size of the map.
     *
     * @param a_key the key of the entry
     *
     * @return the value itself
     */
    ValueType& At(const KeyType& a_key);

    /**
     * @brief Gets the value at the given key.
     *
     * @details Runtime: O(n), where n is the used size of the map.
     *
     * @param a_key the key of the entry
     *
     * @return the value itself
     */
    ValueType& Get(const KeyType& a_key) const;

    /**
     * @brief Finds the iterator corresponding to the given key.
     *
     * @details Runtime: O(n), where n is the used size of the map.
     *
     * @param a_key the key of the entry
     *
     * @return the iterator for the entry itself
     */
    Iterator Find(const KeyType& a_key) const;

    /**
     * @brief Checks if an entry with the given key exists.
     *
     * @details Runtime: O(n), where n is the used size of the map.
     *
     * @param a_key the key to check
     * @return if the entry exists
     */
    Bool Exists(const KeyType& a_key) const;

    /**
     * @brief Inserts an entry with the given key and value.
     *
     * @details Runtime:
     *  - no resize necessary: O(n), where n is the used size of the map.
     *  - resize necessary: O(n), where n is the capacity of the map.
     *
     * @param a_key the key of the new entry
     * @param a_value the value of the new entry
     */
    void Insert(const KeyType& a_key, const ValueType& a_value);

    /**
     * @brief Removes the entry with the given key
     *
     * @details Runtime: O(n), where n is the used size of the map.
     *
     * @param a_key the key of the entry to remove
     */
    void Remove(const KeyType& a_key);

    /**
     * @brief Resizes the map to double its capacity.
     *
     * @details Runtime: O(n), where n is the capacity of the map.
     *
     * @param a_new_capacity the new capacity of the map
     */
    void Resize(Size a_new_capacity);

    /**
     * @brief Gets how much size is occupied in the map.
     *
     * @details Runtime: O(1)
     *
     * @return the used size
     */
    Size GetSize() const;

    /**
     * @brief Converts the map to a string.
     *
     * @details Runtime: O(n), where n is the used size of the map.
     *
     * @return the map as a string
     */
    String ToString() const;

    ValueType& operator[](const KeyType& a_key);
    const ValueType& operator[](const KeyType& a_key) const;

    /**
     * @brief Gets the beginning of the iterator.
     * @return the iterator at the beginning
     */
    Iterator begin() const;
    /**
     * @brief Gets the end of the iterator.
     * @return the iterator at the end
     */
    Iterator end() const;

  private:
    /**
     * @brief Converts the given key to the corresponding index.
     *
     * @details Runtime: O(n), where n is the length of the key.
     *
     * @param a_key the key to convert
     * @return the key converted to an index
     */
    Size keyToIndex(const KeyType& a_key) const;
    /**
     * @brief Finds the entry corresponding to the given key.
     *
     * @details Runtime:
     *  - key length > used size of map: O(n), where n is the length of the key.
     *  - key length = used size of map: O(n), where n is the length of the key & used size of the array.
     *  - key length < used size of map: O(n), where n is the used size of the array.
     *
     * @param a_key the key of the entry
     * @return the pointer to the entry
     */
    Entry* find(const KeyType& a_key) const;
    /**
     * @brief Calculates the hash of the given key using the given algorithm.
     *
     * @details Runtime: O(n), where n is the length of the key.
     *
     * @param a_algorithm the algorithm to use for hashing
     * @param a_key the key to hash
     * @return the hashed key
     */
    U64 calculateHash(algorithms::Hash a_algorithm, const String& a_key) const;

    /**
     * @brief Hashes the given key using the DJB2 algorithm.
     *
     * @details Runtime: O(n), where n is the length of the key.
     *
     * @param a_key the key to hash
     * @return the hashed key
     */
    static U64 hashDJB2(const char* a_key);
    /**
     * @brief Hashes the given key using the SDBM algorithm.
     *
     * @details Runtime: O(n), where n is the length of the key.
     *
     * @param a_key the key to hash
     * @return the hashed key
     */
    static U64 hashSDBM(const char* a_key);
    /**
     * @brief Hashes the given key using the FNV-1a algorithm.
     *
     * @details Runtime: O(n), where n is the length of the key.
     *
     * @param a_key the key to hash
     * @return the hashed key
     */
    U64 hashFNV1a(const char* a_key) const;
  };

  // --------------
  // PUBLIC METHODS
  // --------------
  template <typename KeyType, typename ValueType>
  Map<KeyType, ValueType>::Map(Size a_capacity, algorithms::Hash a_algorithm, Float a_grow_factor,
                               Bool a_growable)
    : m_capacity{a_capacity}, m_used{0}, m_algorithm{a_algorithm}, m_grow_factor(a_grow_factor),
      m_growable(a_growable) {
    m_entries = new Entry[m_capacity];

    for(int i = 0; i < m_capacity; i++)
      m_entries[i].used = false;
  }

  template <typename KeyType, typename ValueType>
  Map<KeyType, ValueType>::Map(const Map<KeyType, ValueType>& a_other)
    : m_capacity{a_other.m_capacity}, m_used{a_other.m_used}, m_algorithm{a_other.m_algorithm},
      m_grow_factor(a_other.m_grow_factor), m_growable(a_other.m_growable) {
    m_entries = new Entry[m_capacity];

    for(Size i = 0; i < m_capacity; ++i)
      m_entries[i].used = false;

    for(Size i = 0; i < m_capacity; ++i) {
      if(!a_other.m_entries[i].used)
        continue;

      Insert(a_other.m_entries[i].key, a_other.m_entries[i].value);
    }
  }

  template <typename KeyType, typename ValueType>
  Map<KeyType, ValueType>::Map(const Map<KeyType, ValueType>& a_other, Size a_capacity)
    : m_capacity{a_other.m_capacity}, m_used{a_other.m_used}, m_algorithm{a_other.m_algorithm},
      m_grow_factor(a_other.m_grow_factor), m_growable(a_other.m_growable) {
    m_entries = new Entry[m_capacity];

    for(Size i = 0; i < m_capacity; ++i)
      m_entries[i].used = false;

    for(Size i = 0; i < m_capacity; ++i) {
      if(!a_other.m_entries[i].used)
        continue;

      Insert(a_other.m_entries[i].key, a_other.m_entries[i].value);
    }

    Resize(a_capacity);
  }

  template <typename KeyType, typename ValueType>
  Map<KeyType, ValueType>::~Map() {
    delete[] m_entries;
  }

  template <typename KeyType, typename ValueType>
  String Map<KeyType, ValueType>::ToString() const {
    String result = "Map(";
    Size appended = 0;

    for(Size i = 0; i < m_capacity; ++i) {
      if(!m_entries[i].used)
        continue;

      result += m_entries[i].key;
      result += " : ";
      result.Append(m_entries[i].value);
      appended++;

      if(appended < m_used)
        result += ", ";
    }

    result += ")";

    return result;
  }

  template<typename KeyType, typename ValueType>
  ValueType& Map<KeyType, ValueType>::operator[](const KeyType& a_key) {
    return At(a_key);
  }

  template<typename KeyType, typename ValueType>
  const ValueType& Map<KeyType, ValueType>::operator[](const KeyType& a_key) const {
    return Get(a_key);
  }

  template <typename KeyType, typename ValueType>
  Bool Map<KeyType, ValueType>::Exists(const KeyType& a_key) const {
    return find(a_key);
  }

  template <typename KeyType, typename ValueType>
  ValueType& Map<KeyType, ValueType>::At(const KeyType& a_key) {
    auto* entry = find(a_key);

    if(!entry) {
      Insert(a_key, {});
      entry = find(a_key);
    }

    return entry->value;
  }

  template <typename KeyType, typename ValueType>
  ValueType& Map<KeyType, ValueType>::Get(const KeyType& a_key) const {
    auto* entry = find(a_key);
    VERIFY(entry && "No entry at key found")
    return entry->value;
  }

  template <typename KeyType, typename ValueType>
  typename Map<KeyType, ValueType>::Iterator Map<KeyType, ValueType>::Find(const KeyType& a_key) const {
    auto* entry = find(a_key);
    if(!entry)
      return end();

    return {entry};
  }

  template <typename KeyType, typename ValueType>
  void Map<KeyType, ValueType>::Insert(const KeyType& a_key, const ValueType& a_value) {
    if(m_growable && m_used >= m_capacity * m_grow_factor)
      Resize(m_capacity * 2);

    int index = keyToIndex(a_key);
    while(m_entries[index].used) {
      if(m_entries[index].key == a_key) {
        m_entries[index].value = a_value;
        return; // Value replaced, so return early
      }

      index = (index + 1) % m_capacity;
    }

    m_entries[index].key = a_key;
    m_entries[index].value = a_value;
    m_entries[index].used = true;

    m_used++;
  }

  template <typename KeyType, typename ValueType>
  void Map<KeyType, ValueType>::Remove(const KeyType& a_key) {
    int index = keyToIndex(a_key);

    while(m_entries[index].used) {
      if(m_entries[index].key == a_key) {
        m_entries[index].used = false;
        m_used--;
        return;
      }
      index = (index + 1) % m_capacity;
    }

    VERIFY(false && "No entry at key found")
  }

  template <typename KeyType, typename ValueType>
  void Map<KeyType, ValueType>::Resize(Size a_new_capacity) {
    VERIFY(a_new_capacity >= m_used);
    VERIFY(a_new_capacity > m_capacity)

    int old_capacity = m_capacity;
    Entry* old_entries = m_entries;

    m_capacity = a_new_capacity;
    m_entries = new Entry[m_capacity];

    for(Size i = 0; i < m_capacity; ++i)
      m_entries[i].used = false;

    for(Size i = 0; i < old_capacity; ++i) {
      if(!old_entries[i].used)
        continue;

      int index = keyToIndex(old_entries[i].key);
      while(m_entries[index].used) {
        index = (index + 1) % m_capacity;
      }

      m_entries[index].key = old_entries[i].key;
      m_entries[index].value = old_entries[i].value;
      m_entries[index].used = true;
    }

    delete[] old_entries;
  }

  template <typename KeyType, typename ValueType>
  Size Map<KeyType, ValueType>::GetSize() const {
    return m_used;
  }

  template <typename KeyType, typename ValueType>
  typename Map<KeyType, ValueType>::Iterator Map<KeyType, ValueType>::begin() const {
    Entry* ptr = m_entries;
    while(!ptr->used && ptr != (m_entries + m_capacity)) ptr++;
    return Iterator(ptr);
  }

  template <typename KeyType, typename ValueType>
  typename Map<KeyType, ValueType>::Iterator Map<KeyType, ValueType>::end() const {
    return Iterator(m_entries + m_capacity);
  }

  // ---------------
  // PRIVATE METHODS
  // ---------------
  template <typename KeyType, typename ValueType>
  typename Map<KeyType, ValueType>::Entry* Map<KeyType, ValueType>::find(const KeyType& a_key) const {
    int index = keyToIndex(a_key);

    while(m_entries[index].used) {
      if(m_entries[index].key == a_key)
        return &m_entries[index];

      index = (index + 1) % m_capacity;
    }

    return nullptr;
  }

  template <typename KeyType, typename ValueType>
  Size Map<KeyType, ValueType>::keyToIndex(const KeyType& a_key) const {
    if constexpr(std::is_same<KeyType, String>::value) {
      return calculateHash(m_algorithm, static_cast<String>(a_key).GetCString()) % m_capacity;
    } else if constexpr(std::is_same<KeyType, std::string>::value) {
      return calculateHash(m_algorithm, static_cast<std::string>(a_key).c_str()) % m_capacity;
    } else if constexpr(std::is_integral<KeyType>::value) {
      return static_cast<Size>(a_key) % m_capacity;
    } else {
      VERIFY(false && "invalid KeyType passed")
    }
  }

  template <typename KeyType, typename ValueType>
  U64 Map<KeyType, ValueType>::calculateHash(algorithms::Hash a_algorithm, const String& a_key) const {
    U64 result;
    switch(a_algorithm) {
      case algorithms::Hash::FNV1a:
        result = hashFNV1a(a_key.GetCString());
        break;
      case algorithms::Hash::DJB2:
        result = hashDJB2(a_key.GetCString());
        break;
      case algorithms::Hash::SDBM:
        result = hashSDBM(a_key.GetCString());
        break;
      default:
        VERIFY(false && "Unknown hashing algorithm");
        break;
    }

    return result;
  }

  template <typename KeyType, typename ValueType>
  U64 Map<KeyType, ValueType>::hashDJB2(const char* a_key) {
    U64 hash = 5381;
    int c;

    while((c = static_cast<unsigned char>(*(a_key++))))
      hash = ((hash << 5) + hash) + c;

    return hash;
  }

  template <typename KeyType, typename ValueType>
  U64 Map<KeyType, ValueType>::hashSDBM(const char* a_key) {
    U64 hash = 0;
    int c;

    while((c = static_cast<unsigned char>(*(a_key++))))
      hash = c + (hash << 6) + (hash << 16) - hash;

    return ((hash & 0x7FFFFFFFFFFFFFFF) | 1);
  }

  template <typename KeyType, typename ValueType>
  U64 Map<KeyType, ValueType>::hashFNV1a(const char* a_key) const {
    const size_t FNV_prime = 1099511628211ULL;
    const size_t FNV_offset = 14695981039346656037ULL;

    U64 hash = FNV_offset;

    int c;
    while((c = static_cast<unsigned char>(*(a_key++))))
      hash = (hash ^ c) * FNV_prime;

    return hash;
  }
}

#endif // NTL_MAP_HPP
