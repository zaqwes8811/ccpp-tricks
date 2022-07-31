
#include <vector>

#include "test_type.hpp"

using namespace std;

template<typename Container, typename Index>
// auto 
decltype(auto)
authAndAccess(
	//Container& c
	Container&& c
, Index i) // -> decltype(c[i])
{
  //authenticateUser();
  return std::forward<Container>(c)[i];
}

vector<int> makeVec() {
	return {1, 5, 6};
}


int main() {

	vector<int> v{1, 5, 6};
	authAndAccess(v, 0) = 1;

	auto s = authAndAccess(makeVec(), 0);
	return 0;
}