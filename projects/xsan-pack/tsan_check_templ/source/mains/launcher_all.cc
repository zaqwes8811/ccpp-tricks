#include <thread>

// FIXME: use boost::thread. Need rebuild boost and libstdc++?

int main() {
    int X;
    std::thread t([&] { X = 42;});
    X = 43;
    t.join();
}
