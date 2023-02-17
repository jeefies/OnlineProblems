#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <set>

using namespace std;
const int N = 57, SEED = 5201314, BASE = 131, BASE2 = 97;


typedef unsigned int hashInt;
int n;
int mapA[N][N], mapB[N][N];
set<hashInt> all;

inline hashInt calc(int mp[N][N], int i, int j, int k) {
	int ha(0), lha(0);
	for (int x = i; x <= i + k; ++x) {
		lha = 0;
		for (int y = j; y <= j + k; ++y) {
			lha = lha * BASE + mp[x][y];
		}
		ha = ha * BASE2 + lha;
	}
	return ha;
}

int main() {
	scanf("%d", &n);
	
	// read map
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			scanf("%d", mapA[i] + j);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			scanf("%d", mapB[i] + j);
	}
	
	for (int k = n - 1; k; --k) {
		// Ã¶¾Ù³¤¶È - 1
		all.clear();
		
		for (int i = 1; i <= n; ++i) {
			if (i + k > n) break;
			for (int j = 1; j <= n; ++j) {
				if (j + k > n) break;
				all.insert(calc(mapA, i, j, k));
			}
		}
		
		for (int i = 1; i <= n; ++i) {
			if (i + k > n) break;
			for (int j = 1; j <= n; ++j) {
				if (j + k > n) break;
				hashInt h = calc(mapB, i, j, k);
				if (all.find(h) != all.end()) {
					printf("%d\n", k + 1);
					return 0;
				}
			}
		}
	}
	printf("1\n");
	return 0;
}
