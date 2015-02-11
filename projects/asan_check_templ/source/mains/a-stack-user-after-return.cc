
// ASAN_OPTIONS=detect_stack_use_after_return=1

int * g;

void LeakLocal() {
	int local;
	g = &local;
}

int main(int argc, char **argv) {
	LeakLocal();
	return *g;
}
