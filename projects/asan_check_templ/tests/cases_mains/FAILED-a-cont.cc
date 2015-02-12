#include <vector>
int main(int argc, char **argv) {
	// http://stackoverflow.com/questions/19673311/stl-vector-resize-and-assign
	std::vector<int> V(8);
	V.resize(5);
	//return V.data()[6];  
	return V[6];  
}

/**
Ubuntu clang version 3.4.2-3ubuntu2~xedgers (tags/RELEASE_34/dot2-final) (based on LLVM 3.4.2)
Target: x86_64-pc-linux-gnu
Thread model: posix

*/
