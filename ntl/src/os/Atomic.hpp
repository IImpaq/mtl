/**
* @file Atomic.hpp
* @author Marcus Gugacs
* @date 10/31/2024
* @copyright Copyright (c) 2024 Marcus Gugacs. All rights reserved.
*/

#ifndef NTL_ATOMIC_HPP
#define NTL_ATOMIC_HPP

#include <atomic>
#include <type_traits>

#include <core/Assert.hpp>

namespace ntl {
  template <typename T>
  class Atomic {
  private:
    std::atomic<T> m_value;

  public:
    CVERIFY(std::is_trivially_copyable_v<T> && "T must be trivially copyable");

    enum class MemoryOrder {
      Relaxed,
      Consume,
      Acquire,
      Release,
      AcquireRelease,
      SequentiallyConsistent
    };

    constexpr Atomic() noexcept = default;
    constexpr explicit Atomic(T a_init_value) noexcept : m_value(a_init_value) {}

    Atomic(const Atomic&) = delete;
    Atomic& operator=(const Atomic&) = delete;

    T Load(MemoryOrder a_order = MemoryOrder::SequentiallyConsistent) const {
      return m_value.load(ConvertMemoryOrder(a_order));
    }

    void Store(T a_value, MemoryOrder a_order = MemoryOrder::SequentiallyConsistent) {
      m_value.store(a_value, ConvertMemoryOrder(a_order));
    }

    T Exchange(T a_value, MemoryOrder a_order = MemoryOrder::SequentiallyConsistent) {
      return m_value.exchange(a_value, ConvertMemoryOrder(a_order));
    }

    bool CompareExchangeWeak(T& expected, T a_value,
                             MemoryOrder success, MemoryOrder failure) {
      return m_value.compare_exchange_weak(expected, a_value,
                                           ConvertMemoryOrder(success),
                                           ConvertMemoryOrder(failure));
    }

    bool CompareExchangeStrong(T& expected, T a_value,
                               MemoryOrder success, MemoryOrder failure) {
      return m_value.compare_exchange_strong(expected, a_value,
                                             ConvertMemoryOrder(success),
                                             ConvertMemoryOrder(failure));
    }

    T FetchAdd(T arg, MemoryOrder a_order = MemoryOrder::SequentiallyConsistent) {
      return m_value.fetch_add(arg, ConvertMemoryOrder(a_order));
    }

    T FetchSub(T arg, MemoryOrder a_order = MemoryOrder::SequentiallyConsistent) {
      return m_value.fetch_sub(arg, ConvertMemoryOrder(a_order));
    }

    T operator++() noexcept { return FetchAdd(1) + 1; }
    T operator++(int) noexcept { return FetchAdd(1); }
    T operator--() noexcept { return FetchSub(1) - 1; }
    T operator--(int) noexcept { return FetchSub(1); }

    operator T() const noexcept { return Load(); }

    T operator=(T a_value) noexcept {
      Store(a_value);
      return a_value;
    }

  private:
    static std::memory_order ConvertMemoryOrder(MemoryOrder a_order) {
      switch(a_order) {
        case MemoryOrder::Relaxed: return std::memory_order_relaxed;
        case MemoryOrder::Consume: return std::memory_order_consume;
        case MemoryOrder::Acquire: return std::memory_order_acquire;
        case MemoryOrder::Release: return std::memory_order_release;
        case MemoryOrder::AcquireRelease: return std::memory_order_acq_rel;
        case MemoryOrder::SequentiallyConsistent: return std::memory_order_seq_cst;
        default: return std::memory_order_seq_cst;
      }
    }
  };
}

#endif // NTL_ATOMIC_HPP
