//
// Created by zaqwes on 14.01.2021.
//

#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>
#include <variant>

using namespace std;
using namespace testing;

//===========================================================================================
//===========================================================================================
//===========================================================================================

// task:
// мовабле передать дальшы, но это поле класса

// task:
// передать лямбду, с минимумом копиования

// task:
// move to lamda

TEST(Cpp, MoveLambdas) {

}

//==7=========================================================================================
//===========================================================================================
//===========================================================================================

// https://en.cppreference.com/w/cpp/utility/any
// https://en.cppreference.com/w/cpp/utility/variant/operator_cmp

class Setter {
public:
  static void set(int32_t v) {}

  static void set(double v) {}

};

enum MessageType {
  INT32 = 0, DOUBLE
};

template<MessageType>
struct Map;

template<>
struct Map<INT32> {
  using type = int32_t;
  static constexpr type value = 0;
};

template<>
struct Map<DOUBLE> {
  using type = double;
  static constexpr type value = 0.;
};

template<MessageType A>
typename Map<A>::type map_attr() { return Map<A>::value; }

using Value = std::variant<int32_t, double>;

// https://en.cppreference.com/w/cpp/language/template_parameters
template<enum MessageType T, typename V>
auto special_get(const V &v) {
  if (std::holds_alternative<decltype(map_attr<T>())>(v)) {
    return std::get<decltype(map_attr<T>())>(v);
  } else {
    throw runtime_error("Has no such type");
  }
}

void sw() {
  // https://www.reddit.com/r/cpp_questions/comments/c0mfwp/improve_a_code_to_map_an_enum_to_a_type/
  // "Discriminating on type via an enum is a known anti-pattern."
}

TEST(Cpp, VariantEnumAny) {
  static_assert(std::is_same<decltype(map_attr<INT32>()), int32_t>::value, "!");
  static_assert(std::is_same<decltype(map_attr<DOUBLE>()), double>::value, "!");

  Value v = 8;
  EXPECT_THROW(std::get<decltype(map_attr<DOUBLE>())>(v), std::bad_variant_access);
  EXPECT_NO_THROW(std::get<decltype(map_attr<INT32>())>(v));
//  EXPECT_NO_THROW(special_get<INT32, int32_t>(v));
  auto read_v = special_get<INT32>(v);

  static_assert(std::is_same<decltype(read_v), int32_t>::value, "!");
  EXPECT_TRUE(std::holds_alternative<decltype(map_attr<INT32>())>(v));

  // int value to type
  // https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
}

//===========================================================================================
//===========================================================================================
//===========================================================================================

TEST(Cpp, VariantCompare) {

}

//===========================================================================================
//===========================================================================================
//===========================================================================================

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}