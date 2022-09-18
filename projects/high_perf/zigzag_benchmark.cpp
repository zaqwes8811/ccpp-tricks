//
// Created by zaqwes on 17.09.2022.
//

#include <benchmark/benchmark.h>

#include "zigzag.hpp"

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "\n\t"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

// Define another benchmark
static const int g_size = 256;
static const int g_num_row = 2;
static void BM_ZigZag(benchmark::State& state) {
    std::string x = gen_random(state.range(0));
    for (auto _ : state) {
        auto result = leetcode::convert_base(x, g_num_row);
        benchmark::DoNotOptimize(result);
    }
}


BENCHMARK(BM_ZigZag)->Arg(8)->Arg(16)->Arg(32)->Arg(64)->Arg(128)->Arg(g_size)->Arg(512);

static void BM_ZigZag_best(benchmark::State& state) {
    std::string x = gen_random(state.range(0));
    for (auto _ : state) {
        auto result = leetcode::convert_best(x, g_num_row);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_ZigZag_best)->Arg(8)->Arg(16)->Arg(32)->Arg(64)->Arg(128)->Arg(g_size)->Arg(512);

static void BM_ZigZag_ref(benchmark::State& state) {
    std::string x = gen_random(state.range(0));
    for (auto _ : state) {
        auto result = leetcode::convert_ref(x, g_num_row);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_ZigZag_ref)->Arg(8)->Arg(16)->Arg(32)->Arg(64)->Arg(128)->Arg(g_size)->Arg(512);