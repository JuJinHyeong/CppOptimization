#include <iostream>
#include <chrono>
using namespace std;

int main() {
	using namespace chrono;
	volatile long long a = 0;
	long long b = 0;

	auto startTime = high_resolution_clock::now();
	for (int i = 1; i < 1'000'000'000; i++) {
		a = a * 3 + 10;
	}
	auto endTime = high_resolution_clock::now();
	cout << "duration: " << duration_cast<milliseconds>(endTime - startTime).count() 
		<< "ms a: " << a << '\n' << endl;

	startTime = high_resolution_clock::now();
	for (int i = 1; i < 1'000'000'000; i++) {
		b = b * 3 + 10;
	}
	endTime = high_resolution_clock::now();
	cout << "duration: " << duration_cast<milliseconds>(endTime - startTime).count()
		<< "ms b: " << b << '\n' << endl;

	return 0;
}