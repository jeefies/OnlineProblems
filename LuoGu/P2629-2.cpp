#include <iostream>

// 暴力解法，O(n^2), 75%可以过 

const int N = 1e6;
int n;
int news[N];

bool valid(int k) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += news[(i + k) % n];
		if (sum < 0) return false;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	int * ptr = news;
	for (int i = 0; i < n; i++) scanf("%d", ptr++);
	int cnt = 0;
	for (int k = 0; k < n; k++) {
		if (valid(k)) ++cnt;
	}
	std::cout << cnt;
	return 0;
}
