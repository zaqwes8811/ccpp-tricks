#include <gtest/gtest.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char *argv[]) {
    // http://stackoverflow.com/questions/3019630/c-how-to-redirect-stderr-from-system-command-to-stdout-or-file
    dup2(1, 2);  // redirects stderr to stdout below this line.

    testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(print_time) = true;
    return RUN_ALL_TESTS();
}
