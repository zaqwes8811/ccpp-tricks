//
// Created by zaqwes on 10.01.2022.
//

// https://www.youtube.com/watch?v=SGdfPextuAU&ab_channel=CppNow

#include <any>
#include <memory>

using UnifiedMessage = std::any;
using SharedMessage = std::shared_ptr<UnifiedMessage>;
using WeakMessage = std::weak_ptr<UnifiedMessage>;
using UniqueMessage = std::unique_ptr<UnifiedMessage>;
using IpcSharedMessage = std::unique_ptr<UnifiedMessage>; // Special counting

template <typename T> class UnifiedMessageView {
public:
  UnifiedMessageView(SharedMessage msg) : weak_msg_{msg} {
    data_ptr_ = std::any_cast<T>(msg.get());
  }

  T *get() {
    auto c = weak_msg_.lock();
    if (c) {
      return data_ptr_;
    }
    return nullptr;
  }

private:
  T *data_ptr_{};
  WeakMessage weak_msg_{};
};

template <typename T> T *as(UnifiedMessage &msg) {
  try {
    return std::any_cast<T>(&msg);
  } catch (...) {
    return nullptr;
  }
}

template <typename T>
std::unique_ptr<UnifiedMessageView<T>> asView(SharedMessage &msg) {
  try {
    return std::make_unique<UnifiedMessageView<T>>(msg);
  } catch (...) {
    return nullptr;
  }
}

class Tensor {};

// void test() {
//     // Direct
//     UnifiedMessage msg = Tensor{};
//
//     Tensor* t_v = as<Tensor>(msg);
//
//     // Shared
//     auto shared_msg = std::make_shared<UnifiedMessage>(Tensor{});
//
//     auto msg_view = asView<Tensor>(shared_msg);
//
//     Tensor* t = msg_view->get();
// }

// static_assert(std::is_nothrow_move_assignable_v<T>, "NeverMind");
// static_assert(std::is_nothrow_move_constructible_v<T>, "NeverMind");

#include <type_traits>

// https://www.youtube.com/watch?v=NH1Tta7purM&t=2694s&ab_channel=CppCon
#include <memory>
// #include <iostream>

struct Order {
  virtual ~Order() = default;

  virtual void SendOrder() = 0;
};

struct OrderSenderA final : public Order {
  //    __attribute__((noinline))
  void SendOrder() final {
    // std::cout << "A" << std::endl;
    static int i = 0;
    ++i;

    for (int z = 0; z < i; ++z) {
      i += z;
    }
  }
};

static_assert(std::is_move_constructible_v<OrderSenderA>, "A");

struct OrderSenderB {
  void SendOrder() {}
};

struct IOrderManager {
  virtual void MainLoop() = 0;

  virtual ~IOrderManager() = default;
};

template <typename T> struct OrderManager final : public IOrderManager {
  void MainLoop() final {
    for (int i = 9; i < 90; ++i) {
      mOrderSender.SendOrder(); // no virtual cost here
    }
  }

  T mOrderSender;
};

std::unique_ptr<IOrderManager> Manager() {
  return std::make_unique<OrderManager<OrderSenderA>>();
}

// int main() {
//     auto m = Manager();
//     m->MainLoop();
// }