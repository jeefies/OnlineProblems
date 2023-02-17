#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std; 

const int N = 1e3 + 7, INF = 0x3F3F3F3F;

struct Egg {
	int x, y, v;
	bool operator< (const Egg &e) {
		return x < e.x;
	}
};

int n, beg;
Egg eggs[N];

void read() {
	int x0;
	scanf("%d %d", &n, &x0);
	
	eggs[0].x = x0;
	
	Egg * ptr = eggs;
	for (int i = 1; i <= n; ++i) {
		++ptr;
		scanf("%d", &ptr->x);
	}
	
	ptr = eggs;
	for (int i = 1; i <= n; ++i) {
		++ptr;
		scanf("%d", &ptr->y);
	}
	
	ptr = eggs;
	for (int i = 1; i <= n; ++i) {
		++ptr;
		scanf("%d", &ptr->v);
	}
	
	sort(eggs, ptr + 1);
	
	int p = 1; beg = 0;
	while (p) {
		if (beg + p <= n && eggs[beg + p].x <= x0) beg += p, p <<= 1;
		else p >>= 1;
	}
	
	/*
	printf("Beg: %d\n", beg);
	for (int i = 0; i <= n; ++i) {
		printf("P{%d, %d, %d}\n", eggs[i].x, eggs[i].y, eggs[i].v);
	}
	*/
}

static int dp[N][N][2], tim[N][N][2];
void work() {
	memset(tim, 0xFF, sizeof(tim)); // all -1, for uninitialized
	// dp[i][j][0/1] 最终在[i, j]左边或者右边所能获得的最大值
	// tim[i][j][0/1] 达到状态时所用的时间 
	tim[beg][beg][0] = dp[beg][beg][0] = 0;
	tim[beg][beg][1] = dp[beg][beg][1] = 0;
	
	// 0左, 1右 
	// dp[i][j][0] = max{
	// 		dp[i + 1][j][0] + eggs[i].y - eggs[i].v * (tim[i + 1][j][0] + eggs[i + 1].x - eggs[i].x),
	// 		dp[i + 1][j][1] + eggs[i].y - eggs[i].v * (tim[i + 1][j][1] + eggs[j].x - eggs[i].x),
	// }
	// final max{dp[0][n][0], dp[0][n][1]}
	for (int l = 1; l <= n; ++l) { // 区间长度实际为 l + 1, 长度最大为 n + 1 
		// i in [max(beg - l, 0), beg]
		// j = i + l;
		int j, a, b; // a从左，b从右 
		for (int i = max(beg - l, 0); i <= beg && i + l <= n; ++i) {
			j = i + l;
			// dp[i][j][0]
			// i + 1 <= beg <=> i < beg
			if (i == beg) goto RIGHT;
			
			if (tim[i + 1][j][0] != -1) a = dp[i + 1][j][0] + eggs[i].y - eggs[i].v * (tim[i + 1][j][0] + eggs[i + 1].x - eggs[i].x);
			else a = -INF;
			if (tim[i + 1][j][1] != -1) b = dp[i + 1][j][1] + eggs[i].y - eggs[i].v * (tim[i + 1][j][1] + eggs[j].x - eggs[i].x);
			else b = -INF;
			
			if (a > b) {
				dp[i][j][0] = a, tim[i][j][0] = tim[i + 1][j][0] + eggs[i + 1].x - eggs[i].x;
			} else {
				dp[i][j][0] = b, tim[i][j][0] = tim[i + 1][j][1] + eggs[j].x - eggs[i].x;
			}
			// printf("dp[%d][%d][0] = %d (time %d)\n", i, j, dp[i][j][0], tim[i][j][0]);
			
			RIGHT:
			// dp[i][j][1]
			// j > beg
			if (j == beg) continue;
			
			if (tim[i][j - 1][0] != -1) a = dp[i][j - 1][0] + eggs[j].y - eggs[j].v * (tim[i][j - 1][0] + eggs[j].x - eggs[i].x);
			else a = -INF;
			if (tim[i][j - 1][1] != -1) b = dp[i][j - 1][1] + eggs[j].y - eggs[j].v * (tim[i][j - 1][1] + eggs[j].x - eggs[j - 1].x);
			else b = -INF;
			 
			if (a > b) {
				dp[i][j][1] = a, tim[i][j][1] = tim[i][j - 1][0] + eggs[j].x - eggs[i].x;
			} else {
				dp[i][j][1] = b, tim[i][j][1] = tim[i][j - 1][1] + eggs[j].x - eggs[j - 1].x;
			}
			// printf("dp[%d][%d][1] = %d (in {%d, %d}) (time %d)\n", i, j, dp[i][j][1], a, b, tim[i][j][1]);
		}
	}
}

int main() {
	read();
	work();
	printf("%.3lf", (double)max(dp[0][n][0], dp[0][n][1]) / 1000);
	return 0;
}
