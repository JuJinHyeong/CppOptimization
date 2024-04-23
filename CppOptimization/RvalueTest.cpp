#include "RvalueTest.h"
#include <vector>
#include <iostream>
#include "Stopwatch.h"
using namespace std;

void RvalueTest::VectorPushbackTest()
{
	cout << "Vector Pushback vs Emplaceback Test\n";

	Stopwatch sw;
	struct Test {
		int a, b, c;
		Test(int a, int b, int c): a(a), b(b), c(c) {}
	};
	vector<Test> v;
	constexpr int num = 1'000'000;
	v.reserve(num);

	sw.Reset();
	for (int i = 0; i < num; i++) {
		v.push_back({ 1, 2, 3 });
	}
	sw.PrintElapsedTime("push_back rvalue");

	vector<Test> v2;
	v2.reserve(num);
	Test temp = { 1, 2, 3 };
	sw.Reset();
	for (int i = 0; i < num; i++) {
		v2.push_back(temp);
	}
	sw.PrintElapsedTime("push_back reserved lvalue");

	vector<Test> v3;
	v3.reserve(num);
	sw.Reset();
	for (int i = 0; i < num; i++) {
		v3.emplace_back(1, 2, 3);
	}
	sw.PrintElapsedTime("emplace_back");

	vector<Test> v4;
	v4.reserve(num);
	Test temp2 = { 1, 2, 3 };
	sw.Reset();
	for (int i = 0; i < num; i++) {
		v4.emplace_back(temp2);
	}
	sw.PrintElapsedTime("emplace_back lvalue");
}
