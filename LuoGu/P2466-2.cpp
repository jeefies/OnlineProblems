#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using std::min;

const int N = 1e3 + 7;

struct Point {
	int x, y, v;
	bool operator < (const Point & p) const {
		return x < p.x;
	}
} pts[N];

int n, t = 1;

void read() {
	int x0;
	scanf("%d %d", &n, &x0);
	pts[1] = {x0, 0, 0}; ++n;
	
	for (int i = 2; i <= n; ++i) scanf("%d", &pts[i].x);
	for (int i = 2; i <= n; ++i) scanf("%d", &pts[i].y);
	for (int i = 2; i <= n; ++i) scanf("%d", &pts[i].v);
	
	std::sort(pts + 1, pts + 1 + n);
	int p = 1;
	while (p) {
		if (t + p < n && pts[t + p].x <= x0) t += p, p <<= 1;
		else p >>= 1;
	}
}

typedef long long data;

data f[N][N][2];
data prefix[N];
data res = 0;

int main() {
	memset(f, 0x7F, sizeof(f));
	
	read();
	for (int i = 1; i <= n; ++i) prefix[i] = pts[i].v + prefix[i - 1], res += pts[i].y;
	f[t][t][0] = f[t][t][1] = 0;
	
	#define vsum(i, j) (prefix[j] - prefix[i - 1])
	// end f[1][n][0] f[1][n][1]
	// f[i][j][0] = f[i+1][j][1]
	// 				f[i+1][j][0] + (vsum(1, i) + vsum(j + 1, n)) * (pts[i + 1].v - pts[i].v) // v * time
	for (int k = 1; k <= n; ++k) {
		int j;
		for (int i = 1; i + k <= n; ++i) {
			j = i + k;
			f[i][j][0] = min(
					f[i+1][j][0] + (vsum(1, i) + vsum(j + 1, n)) * (pts[i + 1].x - pts[i].x),
					f[i+1][j][1] + (vsum(1, i) + vsum(j + 1, n)) * (pts[j].x - pts[i].x)
				);
			f[i][j][1] = min(
					f[i][j-1][1] + (vsum(1, i - 1) + vsum(j, n)) * (pts[j].x - pts[j - 1].x),
					f[i][j-1][0] + (vsum(1, i - 1) + vsum(j, n)) * (pts[j].x - pts[i].x)
			);
		}
	}
	
	data minCost = min(f[1][n][0], f[1][n][1]);
	printf("%.3lf\n", (double)(res - minCost) / 1000.0);
	return 0;
}