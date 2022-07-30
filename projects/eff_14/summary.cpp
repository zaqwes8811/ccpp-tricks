

// These types are frequently different, because ParamType often contains 
// adornments, e.g., const or reference qualifiers.
template<typename T>
void f(ParamType param);

int main() {
	return 0;
}