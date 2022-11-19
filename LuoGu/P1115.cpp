#include <iostream>

int main() {
	int n, c, maxn = -0x3F3F3F3F, sum = 0; std::cin >> n;
	while (n --> 0) {
		std::cin >> c;
		maxn = std::max(sum = sum < 0 ? c : sum + c, maxn);
	}
	std::cout << maxn;
	return 0;
}
