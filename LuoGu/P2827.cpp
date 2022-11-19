#include <queue>
#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;

#define NDEBUG

int n, m, q, u, v, t;
double p;

const int N = 1e5 + 10;
const int BN = 1e5 + 7e6 + 10;
static int a[N], ai = 0, b[BN], bl;
deque<int> x, y;

int choose() {
	if (ai < n && (x.empty() || a[ai] > x.front()) && (y.empty() || a[ai] > y.front())) return a[ai++];
	int m;
	if (x.front() > y.front()) {
		m = x.front(); x.pop_front();
		return m;
	} else {
		m = y.front(); y.pop_front();
		return m;
	}
	return 0;
}

void mergeXYtoB() {
	int bi = 0; 
	while (x.size() || y.size()) {
		if (y.empty() || (x.front() > y.front())) {
			b[bi] = x.front(); x.pop_front();
		} else {
			b[bi] = y.front(); y.pop_front();
		}
		++bi; 
	}
	bl = bi; 
}

void mergeAB(int offset) {
	int bi = 0;
	int abi = 0, ab;
	while (ai < n || bi < bl) {
		if (ai == n || a[ai] < b[bi]) ab = b[bi++];
		else ab = a[ai++];
		if (++abi % t == 0) printf("%d ", ab + offset);
		// printf("Add %d\n", *(ab - 1));
	}
}

signed main() {
	cin >> n >> m >> q >> u >> v >> t;
	p = (double)u / (double)v;
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	
	sort(a, a + n, [](int &a, int &b) {
		return a > b;
	});
	
	#ifndef NDEBUG
	for (int i = 0; i < n; i++) printf("%d ", a[i]); putchar('\n');
	#endif
	
	
	int offset = 0;
	for (int i = 1; i <= m; i++) {
		int m = choose() + offset;
		offset += q;
		if (i % t == 0) 
			printf("%d ", m);
		int px = (int)(p * m);
		x.push_back(px - offset), y.push_back(m - px - offset);
	
		#ifndef NDEBUG
		printf("\nAi = %d", ai);
		printf("\nA:"); for (int i = ai; i < n; i++) printf("%d ", a[i]);
		printf("\nX:"); for (const int & i : x) printf("%d ", i + offset);
		printf("\nY:"); for (const int & i : y) printf("%d ", i + offset); putchar('\n');
		#endif
	}
	
	putchar('\n');
	mergeXYtoB();
	mergeAB(offset);
	
	return 0;
}
