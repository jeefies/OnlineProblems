extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

#warning 无法处理等高的放在相邻位置的情况

class plc {
public:
	int x, y, h;
	plc(int _x, int _y, int _h) {
		x = _x, y = _y, h = _h;
	}
};

int r, c, plci = 0;
plc * plcs[10000];
int mp[100][100];
int dp[102][102];

int main(int argc, char * argv[]) {
	memset(dp, 0, sizeof(dp));

	scanf("%d%d", &r, &c);

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", mp[i] + j);
			plcs[plci++] = new plc(i+1, j+1, mp[i][j]);
		}
	}

	sort(plcs, plcs + plci, [](plc * a, plc * b){
		return a->h < b->h;
	});

	int gmaxh = 0;
	for (int i = 0; i < plci; i++) {
		int x = plcs[i]->x, y = plcs[i]->y;
		int maxh = 1;
		maxh = max(maxh, dp[x-1][y]+1);
		maxh = max(maxh, dp[x+1][y]+1);
		maxh = max(maxh, dp[x][y+1]+1);
		maxh = max(maxh, dp[x][y-1]+1);
		dp[x][y] = maxh;

		gmaxh = max(maxh, gmaxh);
	}
	cout << gmaxh << endl;
	return 0;
}
