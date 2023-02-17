#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>

int x, y, xy;

// gcd(x, y) = gcd(y, x % y);
int gcd(int x, int y) {
    int t;
	while (y) {
        t = x % y, x = y, y = t;
    }
	return x;
}

int main() {
	scanf("%d %d", &x, &y); xy = x * y;
	int n = 0;
	for (int i = x; i <= xy; i += x) {
		if (y % i == 0 && gcd(i, xy / i) == x) {
			++n;
		}
	}

	printf("%d\n", n);
}
