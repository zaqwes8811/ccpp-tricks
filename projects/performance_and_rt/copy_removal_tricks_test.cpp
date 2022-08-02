//
// Created by zaqwes on 31.12.2021.
//

#include <type_traits>

class WithConst {};

static_assert(std::is_move_assignable_v<WithConst>, "NeverMind");