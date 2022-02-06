//
// Created by zaqwes on 06.02.2022.
//

#include <iceoryx_hoofs/cxx/expected.hpp>

iox::cxx::expected<int, int> v = iox::cxx::expected<int, int>::create_error<int>(1);