#include <vector>
int main(int argc, char **argv) {
	// http://stackoverflow.com/questions/19673311/stl-vector-resize-and-assign
	std::vector<int> V(8);
	V.resize(5);
	//return V.data()[6];  
	return V[6];  
}
