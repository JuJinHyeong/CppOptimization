#include "DynamicMemoryTest.h"
#include <iostream>
#include "Stopwatch.h"
using namespace std;

void DynamicMemoryTest::Example()
{
	struct Test {
		char* p;
		Test(const char* str) : p(new char[strlen(str) + 1]) {
			memcpy(p, str, strlen(str) + 1);
		}
		~Test() {
			cout << "Remove Test\n";
			delete[] p;
		}
	};
	char* cp;
	Test* tp = nullptr;
	int n = 100;
	cp = new char[n];
	tp = new Test("hello");

	char array[sizeof(Test)];
	Test* tp2 = new(array) Test("world");

	delete[] cp;
	cp = new char;

	delete tp;
	delete cp;
	// what is different between tp2->~Test() and delete tp2?
	tp2->~Test();
	//delete tp2;
}

void DynamicMemoryTest::NewDeleteTest()
{
	cout << "New Delete Test\n";
	Stopwatch sw;

}
