
// Need options
// ASAN_OPTIONS="detect_leaks=1 symbolize=1" out/Release/base_unittests
// FIXME: must work
//   https://code.google.com/p/address-sanitizer/wiki/LeakSanitizer

int *g = new int;

int main() {
	g = 0;
	//int *g = new int;
	return 0;
}
