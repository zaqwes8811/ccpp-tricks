
struct s{
	int f(int argc) {
			int* array = new int[100];
		delete [] array;
		return array[argc];  // +100 not working
	}
};

int main(int argc, char **argv) {
	return s().f(argc);
}
