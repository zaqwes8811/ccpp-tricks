#include <benchmark/benchmark.h>

#include <ctime>
#include <iostream>
#include <unistd.h>

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

std::string remove_ctrl(std::string s) {
    std::string result;
    for (int i=0; i<s.length(); ++i) {
        if (s[i] >= 0x20)
            result = result + s[i];
    }
    return result;
}

// Define another benchmark
static void BM_remove_ctrl(benchmark::State &state) {
    std::string x = gen_random(128);
    for (auto _ : state) {
        auto result = remove_ctrl(x);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_remove_ctrl);

std::string remove_ctrl_mutating(std::string s) {
    std::string result;
    for (int i=0; i<s.length(); ++i) {
        if (s[i] >= 0x20)
            result += s[i];
    }
    return result;
}

// Define another benchmark
static void BM_remove_ctrl_mutating(benchmark::State &state) {
    std::string x = gen_random(128);
    for (auto _ : state) {
        auto result = remove_ctrl_mutating(x);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_remove_ctrl_mutating);

std::string remove_ctrl_reserve(std::string s) {
    std::string result;
    result.reserve(s.length());
    for (int i=0; i<s.length(); ++i) {
        if (s[i] >= 0x20)
            result += s[i];
    }
    return result;
}

// Define another benchmark
static void BM_remove_ctrl_reserve(benchmark::State &state) {
    std::string x = gen_random(128);
    for (auto _ : state) {
        auto result = remove_ctrl_reserve(x);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_remove_ctrl_reserve);