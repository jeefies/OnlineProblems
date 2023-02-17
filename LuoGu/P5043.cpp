#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 53, BASE[2] = {97, 131};

template<typename T>
inline void read(T &x) {
	register char tmp, f(0); x = 0;
	do if ((tmp = getchar()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
	do x = (x<<1) + (x<<3) + (tmp ^ 48), tmp = getchar(); while ('0' <= tmp && tmp <= '9');
	if (f) x = -x;
}
template <typename T, typename ...Args>
inline void read(T &x, Args&... args) {
	read(x), read(args...);
}

typedef unsigned long long hashInt;

class Graph {
private:
	int n;
	vector<int> siz;
	vector<int> G[N];
public:
	hashInt Ghash;
	inline void add(int u, int v) {
		G[u].push_back(v);
	}
	inline void input() {
		read(n);
		for (int x, i = 1; i <= n; ++i) {
			read(x);
			if (x) add(x, i), add(i, x);
		}
	}
	
	inline hashInt hash(int x, int fa) {
		vector<hashInt> hs;
		for (auto &y : G[x]) {
			if (y ^ fa) {
				hs.push_back(hash(y, x));
				siz[x] += siz[y];
			}
		}
		sort(hs.begin(), hs.end());
		hashInt ha(siz[x]);
		for (auto &h : hs) {
			ha = ha * BASE[siz[x] & 1] + h;
		}
		return ha;
	}
	
	inline void prepare() {
		for (int x(1); x <= n; ++x) {
			siz.assign(n + 1, 1);
			Ghash = max(Ghash, hash(x, 0));
		}
	}
};

static Graph g[N];
int main() {
	int m;
	read(m);
	
	for (int i(1); i <= m; ++i) {
		g[i].input();
		g[i].prepare();
	}
	
	static int grp[N];
	for (int i(1); i <= m; ++i) {
		if (!grp[i]) {
			grp[i] = i;
			for (int j = i + 1; j <= m; ++j) {
				if (g[i].Ghash == g[j].Ghash) grp[j] = i;
			}
		}
		printf("%d\n", grp[i]);
	}
	return 0;
}
