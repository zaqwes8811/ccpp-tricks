#include <gtest/gtest.h>

#include <iostream>
#include <iterator>
#include <list>
#include <memory_resource>

template <typename T>
class RecyclableQueue final {
public:
    RecyclableQueue(int StartSize = 64)
        : start_size_{StartSize},
          arena_(start_size_ * sizeof(T) * 4),
          pool_{std::data(arena_), std::size(arena_)},
          list_(&pool_),
          reusable_list_{&pool_} {}

    void Push(T data) {
        if (std::empty(reusable_list_)) {
            list_.push_back(std::move(data));
            return;
        }

        auto it = std::begin(reusable_list_);
        *it = std::move(data);
        list_.splice(list_.end(), reusable_list_, it);
    }

    bool empty() const { return list_.empty(); }

    decltype(auto) Pop() {
        auto it = std::begin(list_);
        auto data = std::move(*it);
        reusable_list_.splice(reusable_list_.end(), list_, it);
        return data;
    }

private:
    int start_size_;
    std::vector<uint8_t> arena_;
    std::pmr::monotonic_buffer_resource pool_;
    std::pmr::list<T> list_;
    std::pmr::list<T> reusable_list_;
};

TEST(RecyclableQueueTest, Creation) {
    RecyclableQueue<int> q;

    q.Push(1);
    q.Push(2);

    EXPECT_EQ(q.Pop(), 1);

    q.Push(3);

    EXPECT_EQ(q.Pop(), 2);

    q.Push(4);
    q.Push(5);

    q.Pop();
    q.Push(6);
}