
#include <vector>

using namespace std;

template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) // -> decltype(c[i])
{
  //authenticateUser();
  return c[i];
}

int main() {

	vector<int> v{1, 5, 6};
	authAndAccess(v, 0) = 1;
	return 0;
}