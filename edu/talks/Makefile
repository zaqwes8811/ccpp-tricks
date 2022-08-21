

all:
	g++ -S -std=c++17 -O3 jt_perf.cpp

ir:
	clang++ -S -std=c++17 -O3 -emit-llvm jt_perf.cpp


clean:
	rm -rf *.out *.ll *.s