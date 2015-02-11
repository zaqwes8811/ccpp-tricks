
int main(int argc, char **argv) {
	int* array = new int[100];
	int res = array[argc + 100];
	delete [] array;
	return res;//stack_array[argc + 100];  // +100 not working
}
