/**
* @file Singleton.hpp
* @author Marcus Gugacs
* @date 10/31/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_SINGLETON_HPP
#define NTL_SINGLETON_HPP

namespace ntl {
#define SINGLETON_IMPL(Derived) friend class Singleton<Derived>;

  /**
   * @brief Singleton Base class to derive custom Singletons from.
   *
   * @tparam T the derived class
   */
  template <typename T>
  class Singleton {
  public:
    /**
     * @brief Gets the one and only instance of this singleton.
     *
     * @return the reference to the singleton
     */
    static T& Instance() {
      // Uses Meyers Singleton: Guaranteed instantiated on first use and be destroyed on application exit
      // C++11 standard guarantees method thread-local static variables to be initialized in a thread-safe way.
      static T instance;
      return instance;
    }

    /**
     * @brief Deletes Copy-Constructor
     */
    Singleton(const Singleton&) = delete;
    /**
     * @brief Deletes Copy-Assignment Operator
     *
     * @return the reference to the singleton
     */
    Singleton& operator=(const Singleton&) = delete;

  protected:
    /**
     * @brief Default Constructor
     */
    Singleton() {}
    /**
     * @brief Default Destructor
     */
    ~Singleton() {}
  };
}

#endif // NTL_SINGLETON_HPP
