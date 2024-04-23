#include "CvsCpp.h"
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include "Stopwatch.h"
using namespace std;

void CvsCpp::ArrayTest()
{
	cout << "Vector vs Array Test\n";
	Stopwatch sw;
	constexpr int num = 1'000;

	int arr[num] = { 0 };
	sw.Reset();
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			arr[j] = i;
		}
	}
	sw.PrintElapsedTime("stack memory array ");
	
	vector<int> v(num);
	sw.Reset();
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			v[j] = i;
		}
	}
	sw.PrintElapsedTime("vector ");

	int* arr2 = new int[num];
	sw.Reset();
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			arr2[j] = i;
		}
	}
	sw.PrintElapsedTime("heap memory array ");
	delete[] arr2;
}
