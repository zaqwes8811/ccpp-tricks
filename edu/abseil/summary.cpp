//
// Created by zaqwes on 12.09.2022.
//

//
// https://abseil.io/tips/1
#include <string>
#include <string_view>

void TakesCharStar(const char* s) {}

void TakesString(const std::string& s) {}

void TakesStringView(std::string_view s) {  // by value
    const auto str_copy = std::string(s);
}

void AlreadyHasString(const std::string& s) {
    //    TakesCharStar(s.c_str());
    TakesStringView(s);
}

void AlreadyHasCharStar(const char* s) {
    //    TakesString(s);
    TakesStringView(s);
}
