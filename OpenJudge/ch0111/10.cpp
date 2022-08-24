#include <iostream>
#include <algorithm>

#define MAXI 1000000000

using namespace std;

int n;
// relative distance
int rocks[50002] = {0};

struct result {
	int dn, tm;
};

int checkMin(int wantmin) {
	int d = 0, dn = 0;
	for (int i = 1; i <= n; i++) {
		d += rocks[i];
		if (d < wantmin) {
			// delete i
			dn++;
		} else {
			// not delete, clear distance
			d = 0;
		}
	}
	
	// printf("Test min %d, delete %d rocks\n", wantmin, dn);
	return dn;
}

int main() {
	int L, N, M;
	scanf("%d%d%d", &L, &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", rocks + i + 1);
	}
	rocks[N + 1] = L;
	for (int i = N; i >= 0; i--) rocks[i + 1] -= rocks[i];
	n = N + 1;
	
	int l = 0, r = L + 1, mid;
	while (l + 1 < r) {
		mid = (l + r) / 2;
		int dn = checkMin(mid);
		if (dn > M) r = mid;
		else l = mid;
	}
	cout << l << endl;
	return 0;
}
