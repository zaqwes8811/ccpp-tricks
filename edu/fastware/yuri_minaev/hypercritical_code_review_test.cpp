//
// Created by zaqwes on 18.09.2022.
//

// "Aut'o'matic

#include <vector>

void foo(const std::vector<int>& vec) {
    for(auto i = 0; i < vec.size(); ++i) {  // int i. Bad for x64

    }
}
