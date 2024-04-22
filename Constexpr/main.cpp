constexpr int pibonachi(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return pibonachi(n - 1) + pibonachi(n - 2);
}

int main() {
	int arr[5] = { 1, 2, 3, 4, 5 };
	constexpr int a = pibonachi(5);
	constexpr int b = 2;
	int c = b;
	int d = arr[c];
	int e = arr[b];
	int test[b] = { a, 4 };

	return 0;
}