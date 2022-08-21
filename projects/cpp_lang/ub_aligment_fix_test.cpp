//
// Created by zaqwes on 04.01.2022.
//

// https://www.youtube.com/watch?v=_qzMpk-22cc&ab_channel=CppCon
// CppCon 2019: Timur Doumler “Type punning in modern C++”

#include <cstring>
#include <type_traits>

template <typename To, typename From,
          typename = std::enable_if<(sizeof(To) == sizeof(From)) && std::is_trivially_copyable_v<From> &&
                                    std::is_trivially_copyable_v<To>>>
To bit_cast(const From &src) {
    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
}