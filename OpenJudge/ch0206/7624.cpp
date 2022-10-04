extern "C" {
	#include <cstdio>
	#include <cstring>
	#include <cstdlib>
	#include <climits>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int m, n;
int ds[500];

int d(int i, int j) {
	static int tmp[500] = {0};
	static bool inited = false;
	if (!inited) {
		for (int k = 1; k <= m; k++) {
			tmp[k] = ds[k] + tmp[k - 1];
		}
		inited = true;
	}
	
	int r = tmp[j] - tmp[i];
	// printf("Calc d(%d,%d) = %d\n", i, j, r);
	return r;
}

int sinit(int i, int j) {
	int mid = (i + j) / 2;
	
	int sum = 0;
	{
		for (int l = i; l <= mid; l++) {
			sum += d(l, mid);
		}
		
		for (int r = j - 1; r >= mid; r--) {
			sum += d(mid, r);
		}
	}
	
	return sum;
}

// village i to j goto one school
int s(int _i, int _j) {
	static int tmp[500][501] = {0};
	static bool inited = false;
	if (!inited) {
		for (int i = 0; i < m; i++) {
			for (int j = i + 2; j <= m; j++) {
				tmp[i][j] = sinit(i, j);
			}
		}
		inited = true;
	}
	
	// printf("\tGet s(%d,%d) = %d\n", _i, _j, tmp[_i][_j]);
	return tmp[_i][_j];
}

int main(int argc, char * argv[]) {
	cin >> m >> n;
	for (int i = 1; i < m; i++) {
		cin >> ds[i];
	}
	
	/* test for sinit.
	for (int j = 1; j <= 4; j++) {
		printf("s(%d,%d) = %d\n", j, j+1, sinit(j, j+1));
	}
	*/
	
	// manidp[i][j]; first i village to j school
	int maindp[500][501] = {0};
	memset(maindp, 0x7F, sizeof(maindp));
	for (int i = 1; i <= m; i++) {
		maindp[i][1] = s(0, i);
		// printf("maindp[%d][1] is set to %d\n", i, maindp[i][1]);
	}
	
	for (int j = 2; j <= n; j++) {
		for (int ie = j; ie <= m; ie++) {
			// printf("maindp[%d][%d] from %d ", ie, j, maindp[ie][j]);
			for (int sep = 0; sep < ie; sep++) {
				maindp[ie][j] = min(maindp[ie][j], maindp[sep][j - 1] + s(sep, ie));
			}
			
			// printf("change to %d\n", maindp[ie][j]);
		}
	}
	
	cout << maindp[m][n] << endl;
	
	return 0;
}