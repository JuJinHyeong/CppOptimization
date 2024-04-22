#pragma once
#include <chrono>
#include <iostream>
#include <vector>

class Stopwatch {
public:
	Stopwatch()
		: m_start(std::chrono::high_resolution_clock::now()) 
	{
	}

	~Stopwatch() {
	}

	void Reset() {
		m_start = std::chrono::high_resolution_clock::now();
	}

	void PrintElapsedTime() {
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_start);
		std::cout << "Elapsed time: " << diff.count() << "us\n";
	}

	int GetMicroseconds() {
		auto diff = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_start);
		return diff.count();
	}

private:
	std::chrono::high_resolution_clock::time_point m_start;
};