//
// Created by zaqwes on 10.02.2022.
//

// CppCon 2019: Ben Deane “Everyday Efficiency: In-Place Construction (Back to Basics?)”

#include <unordered_map>
#include <vector>

std::vector<std::pair<int, int>> m;

void f() { m.emplace_back(std::piecewise_construct, std::forward_as_tuple(1), std::forward_as_tuple(1)); }