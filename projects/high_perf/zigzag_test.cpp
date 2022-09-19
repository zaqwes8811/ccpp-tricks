//
// Created by zaqwes on 17.09.2022.
//

#include "zigzag.hpp"

#include <gtest/gtest.h>

#include "common/data_generators.hpp"

using namespace std;

TEST(ZigZagTest, Ref) {
    const auto source = gen_random(128);
    const int num_rows = 5;
    EXPECT_EQ(leetcode::convert_ref(source, num_rows), leetcode::convert_base(source, num_rows));
    EXPECT_EQ(leetcode::convert_ref(source, num_rows), leetcode::convert_forge(source, num_rows));
    EXPECT_EQ(leetcode::convert_ref(source, num_rows), leetcode::convert_arena(source, num_rows));
    EXPECT_EQ(leetcode::convert_ref(source, num_rows), leetcode::convert_best1(source, num_rows));
}