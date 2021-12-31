#include <benchmark/benchmark.h>
// intrusive containers
// https://www.boost.org/doc/libs/1_64_0/doc/html/intrusive/intrusive_vs_nontrusive.html
#include <boost/intrusive/list.hpp>

#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <iostream>   // cout
#include <list>
#include <unordered_map>

using namespace std;

template<typename T>
std::vector<T> create_random_data(int n) {
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed); // a source of random data

    std::uniform_int_distribution<T> dist;
    std::vector<T> v(n);

    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

namespace v1 {

template<typename T, class Hash = hash<T>, class Equal = equal_to<T> >
class Lru {
public:
    explicit Lru(size_t max_size) :
        max_size_(max_size) {
    }

    bool Has(const T& key) {
        auto it = map_.find(key);
        if (it == map_.end())
            return false;

        auto list_it = it->second;
        list_.erase(list_it);
        it->second = list_.insert(list_.end(), key);
        return true;
    }

    bool Put(const T& key) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            list_.erase(it->second);
            it->second = list_.insert(list_.end(), key);
            return false;
        }

        if (list_.size() == max_size_) {
            T last = list_.front();
            list_.pop_front();
            map_.erase(last);
        }
        map_[key] = list_.insert(list_.end(), key);
        return true;
    }

private:
    std::list<T> list_;
    std::unordered_map<T, typename std::list<T>::iterator, Hash, Equal> map_;
    std::size_t max_size_;
};

}

// TODO How to plane experiment?
// TODO Lru capacity?
static const vector<unsigned>& keys_for_benchmark() {
    // in order to catch exceptions
    static vector<unsigned> keys = create_random_data<unsigned>(1000);
    return keys;
}

static void BM_v1_lru_Put(benchmark::State& state) {
    // Put to empty
    const auto& keys = keys_for_benchmark();
    auto lru = v1::Lru<unsigned>(keys.size());
    for (auto _ : state) {
        for (const auto& key : keys) {
            lru.Put(key);
        }
    }
}

BENCHMARK(BM_v1_lru_Put);

static void BM_v1_lru_Has(benchmark::State& state) {
    const auto& keys = keys_for_benchmark();
    auto lru = v1::Lru<unsigned>(keys.size());
    for (const auto& key : keys) {
        lru.Put(key);
    }
    for (auto _ : state) {
        for (const auto& key : keys) {
            lru.Has(key);
        }
    }
}

BENCHMARK(BM_v1_lru_Has);

static void BM_v1_lru_PutOverflow(benchmark::State& state) {
    const auto& keys = keys_for_benchmark();
    auto lru = v1::Lru<unsigned>(512);
    for (const auto& key : keys) {
        lru.Put(key);
    }
    for (auto _ : state) {
        for (const auto& key : keys) {
            lru.Put(key);
        }
    }
}

BENCHMARK(BM_v1_lru_PutOverflow);

//// main()
//BENCHMARK_MAIN()
//;
