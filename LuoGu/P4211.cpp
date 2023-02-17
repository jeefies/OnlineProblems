#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

const int N = 5e5 + 7, MOD = 201314;

int readInt() {
	char tmp; int x = 0, f = 1;
	do { if ((tmp = getchar()) == '-') f = -1; } while (tmp < '0' || tmp > '9');
	do { x = x * 10 + tmp - '0', tmp = getchar(); } while ('0' <= tmp && tmp <= '9');
	return x * f;
}

struct Edge {
	int to, next;
} edge[N * 2];
int head[N], tot = 0;
void add(int u, int v) {
	edge[++tot] = {v, head[u]}, head[u] = tot;
}

int n, m, root = 0;
int fa[N], siz[N], dfn[N], dep[N], cdfn = 0;

void read() {
	scanf("%d %d", &n, &m);
	int t;
	for (int i = 1; i < n; ++i) {
		fa[i] = t = readInt();
		add(t, i);
	}
}

void preWork(int x) {
	dfn[x] = ++cdfn;
	dep[x] = dep[fa[x]] + 1;
	siz[x] = 1;
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to; preWork(y);
		siz[x] += siz[y];
	}
}

namespace ST {
	int lg2[N];
	int f[N][21];
	int offset[21] = {1};
	
	inline int Max(int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	
	void init(int n) {
		for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
		for (int i = 1; i <= n; ++i) f[dfn[i]][0] = i;
		int t = lg2[n];
		for (int k = 1; k <= t; ++k) {
			offset[k] = 1 << k;
			for (int i = 1; i + offset[k] - 1 <= n; ++i)
				f[i][k] = Max(f[i][k - 1], f[i + offset[k-1]][k - 1]);
		}
	}
	
	int query(int l, int r) {
		int k = lg2[r - l + 1];
		return Max(f[l][k], f[r - offset[k] + 1][k]);
	}
}

int getLCA(int x, int y) {
	if (x == y) return x;
	if (dfn[x] > dfn[y]) return fa[ST::query(dfn[y] + 1, dfn[x])];
	return fa[ST::query(dfn[x] + 1, dfn[y])];
}

struct Ques {
	int l, r, z, i;
	bool operator< (const Ques & q) {
		if (z < q.z) return r < q.r;
		return z < q.z;
	}
} ques[N];

void readQues() {
	Ques * q = ques;
	for (int i = 1; i <= m; ++i) {
		++q;
		q->l = readInt(), q->r = readInt(), q->z = readInt(), q->i = i;
	}
	std::sort(ques + 1, q + 1);
}

void work() {
	static int prefix[N] = {0};
	static int res[N];
	
	int lz = -1, r = 0;
	Ques * q = ques;
	for (int i = 1; i <= m; ++i) {
		++q;
		if (q->z != lz) r = 0;
		while (r <= q->r) {
			prefix[r + 1] = (dep[getLCA(r, q->z)] + prefix[r]) % MOD;
			++r;
		}
		res[q->i] = prefix[q->r + 1] - prefix[q->l];
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", res[i] % MOD);
	}
}

int main() {
	read();
	preWork(root);
	ST::init(n);
	readQues();
	work();
	return 0;
}