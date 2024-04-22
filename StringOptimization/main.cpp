#include<iostream>
#include<string>
#include "Stopwatch.h"
using namespace std;

string RemoveCtrl(string s) {
	string result;
	for (int i = 0; i < s.length(); ++i) {
		if (i > 0x20) {
			result = result + s[i];
		}
	}
	return result;
}

string RemoveCtrlMutate(string s) {
	string result;
	for (int i = 0; i < s.length(); ++i) {
		if (i > 0x20) {
			result += s[i];
		}
	}
	return result;
}

string RemoveCtrlMutateReserve(string s) {
	string result;
	result.reserve(s.length());
	for (int i = 0; i < s.length(); ++i) {
		if (i > 0x20) {
			result += s[i];
		}
	}
	return result;
}

string RemoveCtrlMutateReserveRef(const string& s) {
	string result;
	result.reserve(s.length());
	for (int i = 0; i < s.length(); ++i) {
		if (i > 0x20) {
			result += s[i];
		}
	}
	return result;
}

string RemoveCtrlMutateReserveRefIt(const string& s) {
	string result;
	result.reserve(s.length());
	for (auto it = s.begin(), end = s.end(); it != end; ++it) {
		if (*it > 0x20) {
			result += *it;
		}
	}
	return result;
}

void RemoveCtrlMutateReserveRefItOut(const string& s, string& out) {
	out.clear();
	out.reserve(s.length());
	for (auto it = s.begin(), end = s.end(); it != end; ++it) {
		if (*it >= 0x20) {
			out += *it;
		}
	}
	return;
}

void RemoveCtrlCString(char* destp, const char* srcp, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		if (srcp[i] >= 0x20) {
			*destp++ = srcp[i];
		}
	}
	*destp = 0;
}

int main() {
	string s;
	for (int i = 0; i < 10000; i++) {
		s.push_back('a');
		s.push_back('b');
		s.push_back('c');
		s.push_back('d');
		s.push_back(' ');
	}
	Stopwatch sw;
	vector<int> times(100, 0);
	char* dest = new char[s.length() + 1];
	for (int i = 0; i < 10; i++) {
		sw.Reset();
		RemoveCtrl(s);
		times[0] += sw.GetMicroseconds();
		
		sw.Reset();
		RemoveCtrlMutate(s);
		times[1] += sw.GetMicroseconds();
		
		sw.Reset();
		RemoveCtrlMutateReserve(s);
		times[2] += sw.GetMicroseconds();
		
		sw.Reset();
		RemoveCtrlMutateReserveRef(s);
		times[3] += sw.GetMicroseconds();
		
		sw.Reset();
		RemoveCtrlMutateReserveRefIt(s);
		times[4] += sw.GetMicroseconds();

		string out;
		sw.Reset();
		RemoveCtrlMutateReserveRefItOut(s, out);
		times[5] += sw.GetMicroseconds();

		sw.Reset();
		RemoveCtrlCString(dest, s.c_str(), s.length());
		times[6] += sw.GetMicroseconds();
	}
	delete[] dest;

	std::cout << "RemoveCtrl: " << times[0] / 100 << "us\n"
		<< "RemoveCtrlMutate: " << times[1] / 100 << "us\n"
		<< "RemoveCtrlMutateReserve: " << times[2] / 100 << "us\n"
		<< "RemoveCtrlMutateReserveRef: " << times[3] / 100 << "us\n"
		<< "RemoveCtrlMutateReserveRefIt: " << times[4] / 100 << "us\n"
		<< "RemoveCtrlMutateReserveRefItOut: " << times[5] / 100 << "us\n"
		<< "RemoveCtrlCString: " << times[6] / 100 << "us\n";

	return 0;
}