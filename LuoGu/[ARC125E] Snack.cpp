#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 5e5 + 3;
typedef long long lint;
struct BC {
	lint b, c;
	double w;
	inline void init() { w = (double)c / b; }
	bool operator < (const BC &o) {
		return w < o.w;
	}
} bc[N];
lint a[N];

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	lint n, m, asum = 0, bsum = 0, csum = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= m; ++i)
		cin >> bc[i].b;
	for (int i = 1; i <= m; ++i)
		cin >> bc[i].c, bc[i].init();
		
	sort(a + 1, a + 1 + n, [](const lint x, const lint y) { return x > y; });
	sort(bc + 1, bc + 1 + m);
	
	for (int i = 1; i <= n; ++i) asum += a[i];
	for (int i = 1; i <= m; ++i) bsum += bc[i].b;
	
	lint minCut = asum;
	BC *ptr = bc + 1, *eptr = bc + 1 + m;
	for (int x = 1; x <= n; ++x) {
		asum -= a[x];
		while (ptr < eptr && ptr->w < x)
			bsum -= ptr->b, csum += ptr->c, ++ptr;
		minCut = min(minCut, x * bsum + csum + asum);
	}
	cout << minCut << '\n';
}