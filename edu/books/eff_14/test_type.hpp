#pragma once

#include <atomic>
#include <iostream>

template <typename PayloadType> struct OptionalPayload {
  PayloadType payload_;
};

template <> struct OptionalPayload<void> {};

template <typename PayloadType = void> struct Checker {
  Checker() {
    std::cout << "Ctor" << std::endl;
    ctor_cnt++;
  }
  Checker(const Checker &) noexcept {
    std::cout << "Copy ctor" << std::endl;
    copy_ctor_cnt++;
  }
  Checker(Checker &&that) noexcept {
    std::cout << "Move ctor" << std::endl;
    that.was_moved_ = true;
    move_ctor_cnt++;
  }

  Checker &operator=(Checker &&that) noexcept {
    std::cout << "Move assignment" << std::endl;
    that.was_moved_ = true;
    move_ctor_cnt++;
    return *this;
  }

  Checker &operator=(const Checker &that) {
    std::cout << "Copy assignment" << std::endl;
    auto tmp = Checker{that};

    std::cout << "Swap" << std::endl;
    swap(tmp, *this);
    copy_ctor_cnt++;
    return *this;
  }

  ~Checker() {
    if (was_moved_) {
      move_dtor_cnt++;
    } else {
      dtor_cnt++;
    }
  }
  void *operator new(size_t size) {
    void *p = ::operator new(size);
    new_cnt++;
    return p;
  }
  void *operator new(size_t, void *place) { return place; }

  void operator delete(void *p) {
    delete_cnt++;
    ::operator delete(static_cast<Checker *>(p));
  }

  static void flush() {
    new_cnt = 0;
    delete_cnt = 0;
    ctor_cnt = 0;
    dtor_cnt = 0;
    copy_ctor_cnt = 0;
    move_ctor_cnt = 0;
    move_assignment_cnt = 0;
    move_dtor_cnt = 0;
  }
  static volatile uint32_t new_cnt;
  static volatile uint32_t delete_cnt;
  static volatile uint32_t ctor_cnt;
  static volatile uint32_t copy_ctor_cnt;
  static volatile uint32_t move_ctor_cnt;
  static volatile uint32_t move_assignment_cnt;
  static volatile uint32_t dtor_cnt;
  static volatile uint32_t move_dtor_cnt;

  bool was_moved_ = false;

  OptionalPayload<PayloadType> payload_;
};

template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::new_cnt = 0;
template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::delete_cnt = 0;
template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::ctor_cnt = 0;
template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::copy_ctor_cnt = 0;
template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::move_ctor_cnt = 0;
template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::move_assignment_cnt = 0;
template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::dtor_cnt = 0;
template <typename PayloadType>
volatile uint32_t Checker<PayloadType>::move_dtor_cnt = 0;

template <typename T> class TD;