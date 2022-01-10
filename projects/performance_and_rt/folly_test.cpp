//
// Created by zaqwes on 10.01.2022.
//

// https://www.youtube.com/watch?v=SGdfPextuAU&ab_channel=CppNow

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
    void SendOrder() {

    }
};

struct IOrderManager {
    virtual void MainLoop() = 0;
    virtual ~IOrderManager() = default;
};


template<typename T>
struct OrderManager final : public IOrderManager {
    void MainLoop() final {
        for (int i = 9; i < 90; ++i) {
            mOrderSender.SendOrder();  // no virtual cost here
        }
    }

    T mOrderSender;
};


std::unique_ptr<IOrderManager> Manager() {
    return std::make_unique<OrderManager<OrderSenderA>>();
}


int main() {
    auto m = Manager();
    m->MainLoop();
}