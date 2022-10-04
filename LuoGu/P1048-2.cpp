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

typedef struct {
	int time, value;
} plant;

int t, m;

int maxv = INT_MIN;
plant plts[101];
int cached[10000];

void prt(int depth) {
	while (depth--) putchar('\t');
}

int ds(int left, int used, int depth) {
	if (cached[left] != 0x7F7F7F7F) return cached[left];
	
	// prt(depth); printf("Stoped when left is %d\n", left);
	if (used == m || left < plts[used].time) return 0;
	
	// prt(depth); printf("search in %d %d\n", left, used);
	
	int best = 0;
	if (left >= plts[used].time) {
		best = plts[used].value + ds(left - plts[used].time, used + 1, depth + 1);
	}
	
	best = max(best, ds(left, used + 1, depth + 1));
	// prt(depth); printf("Get best value %d\n", best);
	
	cached[left] = best;
	
	return best;
}

int main(int argc, char * argv[]) {
	memset(cached, 0x7F, sizeof(cached));
	
	cin >> t >> m;
	for (int i = 0; i < m; i++) {
		cin >> plts[i].time >> plts[i].value;
	}
	sort(plts, plts + m, [](plant & a, plant & b) {
		return a.time < b.time;
	});
	
	cout << ds(t, 0, 0) << endl;
	return 0;
}