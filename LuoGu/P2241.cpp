#include <iostream>

int main() {
	int n, m;
	std::cin >> n >> m;
	long long rect = 0, sqr = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			rect += i * j, sqr += std::min(i, j); 
	}
	std::cout << sqr << ' ' << rect - sqr << std::endl;
	return 0;
} 
