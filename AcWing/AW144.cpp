#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
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

const int N = 5e6 + 7;
int n;

int usage(1);
int kids[N][2], exi[N];
int ans(0);
#define bit(x, i) (((x)>>i) & 1)
#define mark(x, i) ((x) | (1<<(i)))
inline void insert(int x) {
	int p(0), q(0), k, res(0);
	for (int i = 30; i >= 0; --i) {
		k = bit(x, i);
		if (!kids[p][k]) kids[p][k] = ++usage;
		p = kids[p][k];
		
		if (kids[q][k ^ 1]) {
			q = kids[q][k ^ 1], res = mark(res, i);
		} else {
			q = kids[q][k];
		}
	}
	ans = max(ans, res);
}

int D[N];
vector<pair<int, int> > G[N];
void dfs(int x, int s, int fa) {
	insert(s);
	for (auto &p : G[x]) {
		if (p.first ^ fa) {
			dfs(p.first, s ^ p.second, x);
		}
	}
}

int main() {
	int n;
	read(n);
	
	int u, v, w;
	for (int i(1); i ^ n; ++i) {
		read(u, v, w);
		G[u].push_back(make_pair(v, w)), G[v].push_back(make_pair(u, w)); 
	}
	
	dfs(0, 0, n);
	printf("%d\n", ans);
	return 0;
}
