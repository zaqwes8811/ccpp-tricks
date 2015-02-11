int global_array[100] = {-1};
int main(int argc, char **argv) {
	//return global_array[argc + 100];
	return global_array[argc + 5 + 100];  // +100 not working
}
