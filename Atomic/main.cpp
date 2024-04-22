#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
using namespace std;

void AddRangeAtomic(atomic<long long>* a, int start, int end) {
	for (int i = start; i <= end; i++) {
		*a += i;
	}
}

void TestRangeAddAtomic(vector<thread>& threads, int start, int end) {
	using namespace chrono;
	threads.clear();
	atomic<long long> sum(0);

	auto startTime = high_resolution_clock::now();
	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(AddRangeAtomic, &sum, start, end));
	}
	for (int i = 0; i < 10; i++) {
		threads[i].join();
	}
	auto endTime = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(endTime - startTime);

	cout << "Test Range Atomic\nduration: " << duration.count() << "ms sum: " << sum << '\n' << endl;
}

void AddRange(long long* a, int start, int end) {
	for (int i = start; i <= end; i++) {
		*a += i;
	}
}

void TestRangeAdd(vector<thread>& threads, int start, int end) {
	using namespace chrono;
	threads.clear();
	long long sum = 0;

	auto startTime = high_resolution_clock::now();
	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(AddRange, &sum, start, end));
	}
	for (int i = 0; i < 10; i++) {
		threads[i].join();
	}
	auto endTime = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(endTime - startTime);

	cout << "Test Range\nduration: " << duration.count() << "ms sum:" << sum << '\n' << endl;
}

void TestSingleThreadRangeAdd(int start, int end) {
	using namespace chrono;
	long long sum = 0;

	auto startTime = high_resolution_clock::now();
	for (int i = 0; i < 10; i++) {
		AddRange(&sum, start, end);
	}
	auto endTime = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(endTime - startTime);
	cout << "Test Range Single Thread\nduration: " << duration.count() << "ms sum: " << sum << '\n' << endl;
}

void AddRangeLock(mutex* mtx, long long* sum, int start, int end) {
	for (int i = start; i <= end; i++) {
		mtx->lock();
		*sum += i;
		mtx->unlock();
	}
}

void TestMutexThreadRangeAdd(vector<thread>& threads, int start, int end) {
	using namespace chrono;
	threads.clear();
	long long sum = 0;
	mutex mtx;

	auto startTime = high_resolution_clock::now();
	for (int i = 0; i < 10; i++) {
		threads.push_back(thread(AddRangeLock, &mtx, &sum, start, end));
	}
	for (int i = 0; i < 10; i++) {
		threads[i].join();
	}
	auto endTime = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(endTime - startTime);
	cout << "Test Range Mutex\nduration: " << duration.count() << "ms sum: " << sum << '\n' << endl;
}

int main() {
	vector<thread> threads;
	int start = 1;
	int end = 1000000;

	TestRangeAddAtomic(threads, start, end);
	TestRangeAdd(threads, start, end);
	TestSingleThreadRangeAdd(start, end);
	TestMutexThreadRangeAdd(threads, start, end);

	return 0;
}