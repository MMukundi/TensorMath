compilerOptions= -std=c++17

Run: tensorTest
	./tensorTest

tensorTest: Tensor.h tensorTest.cpp
	g++ $(compilerOptions) tensorTest.cpp -o tensorTest