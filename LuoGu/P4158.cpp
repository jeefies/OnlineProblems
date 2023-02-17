#include <iostream>
#include <algorithm>

using namespace std;

const int N = 50 + 3, M = 50 + 3, T = 2500 + 3;
int f[N][M][M];

int n, m, t;
int blue[N][M];

void read() {
	scanf("%d %d %d", &n, &m, &t);
	printf("Read n, m, t: %d %d %d\n", n, m, t);
	
	char tmp;
	for (int i = 1; i <= n; ++i) {
		do {
			tmp = getchar();
		} while (tmp != '0' && tmp != '1');
		int j = 1;
		do {
			blue[i][j] = tmp == '1' ? 1 : 0;
			blue[i][j] += blue[i][j - 1];
			tmp = getchar();
			++j;
		} while (tmp == '0' || tmp == '1');
		printf("Read line %d\n", i);
	}
}

#define g f[x]

void work(int x) {
	int *b = blue[x];
	printf("::");
	for (int i = 1; i <= m; ++i) {
		printf("%d ", b[i]);
		g[i][1] = b[i];
	} putchar('\n');
	
	int se = min(m, t);
	int bl;
	for (int s = 2; s <= se; ++s) {
		for (int i = s; i <= m; ++i) {
			for (int j = 1; j <= i; ++j) {
				bl = b[i] - b[j];
				g[i][s] = max(g[i][s], g[j][s-1] + max(bl, i - j - bl));
			}
		}
	}
}

int main() {
	read();
	for (int i = 1; i <= n; ++i) {
		work(i);
		printf("work %d:\n", i);
		for (int s = 1; s <= m; ++s) {
			for (int j = 1; j <= m; ++j)
				printf("%d ", f[i][j][s]);
			putchar('\n');
		}
	}
}