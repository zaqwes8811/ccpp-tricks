
#include <vector>
#include <type_traits>

#include "test_type.hpp"

using namespace std;

template <typename Container, typename Index>
// auto
decltype(auto) authAndAccess(
    // Container& c
    Container &&c, Index i) // -> decltype(c[i])
{
  // authenticateUser();
  return std::forward<Container>(c)[i];
}

vector<int> makeVec() { return {1, 5, 6}; }

using Vec = Checker<std::vector<int>>;

class Holder {
public:
  Vec steal() { return std::move(v_); }

  Vec &&stealPureRVal() { return std::move(v_); }

  decltype(auto) stealRval() { return std::move(v_); }

  Vec v_;
};

int main() {

  vector<int> v{1, 5, 6};
  authAndAccess(v, 0) = 1;

  auto s = authAndAccess(makeVec(), 0);

  std::cout << "[!] Base" << std::endl;
  {
    Holder h;
    auto v = h.steal();
    // TD<decltype(v)> v_type;
  }

  std::cout << "[!] Next" << std::endl;
  {
    Holder h;
    Vec v;
    v = h.stealRval();

    v = h.stealPureRVal();
    static_assert(std::is_same<decltype(h.stealRval()), Vec&&>());// v_type;

    std::cout << "  [!] Return by value" << std::endl;
    v = h.steal();
  }

  std::cout << "[!] Copy" << std::endl;
  {
    Holder h;
    auto v = Vec{};
    Vec k;
    k = v;
  }
  return 0;
}