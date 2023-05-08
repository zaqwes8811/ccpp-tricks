#include <gtest/gtest.h>

#include <list>
#include <iostream>

template<typename T>
class RecyclableQueue final {
public:
    void Push(T data) {
        if (reusable_list_.empty()) {
            list_.push_back(std::move(data));
            return;
        }

        auto it = std::begin(reusable_list_);
        *it = std::move(data);
        list_.splice(list_.end(), reusable_list_, it);
    }

    decltype(auto) Pop() {
        auto it = std::begin(list_);
        auto data = std::move(*it);
        reusable_list_.splice(reusable_list_.end(), list_, it);
        return data;
    }

private:
    std::list<T> list_;
    std::list<T> reusable_list_;
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