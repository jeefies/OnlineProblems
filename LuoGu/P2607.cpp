#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 1e6 + 7;

using std::max;

struct Edge {
	int to, next;
} edge[N * 2]; int head[N], tot = 0;
void add(int u, int v) {
	edge[++tot] = {v, head[u]}, head[u] = tot;
}

class MergeFindSet {
private:
	int grp[N];
public:
	void init(int n) {
		for (int i = 1; i <= n; ++i) grp[i] = i;
	}
	
	int find(int x) {
		if (x == grp[x]) return x;
		return grp[x] = find(grp[x]);
	}
	
	void merge(int x, int y) {
		grp[find(x)] = find(y);
	}
};

int n;
int rt1[N], rt2[N], cnt = 0;
int w[N];
void read() {
	scanf("%d", &n);
	
	int h, gi, gh;
	static MergeFindSet mfs; mfs.init(n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", w + i, &h);
		if ((gi = mfs.find(i)) == (gh = mfs.find(h))) {
			rt1[++cnt] = i, rt2[cnt] = h;
			// printf("Connect ring %d, %d\n", i, h);
		} else {
			mfs.merge(gi, gh);
			add(i, h), add(h, i);
		}
	}
}

int vis[N] = {0}, vt = 0;
long long f[N][2];
void dp(int x) {
	vis[x] = vt;
	f[x][1] = w[x], f[x][0] = 0;
	
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (vis[y] != vt) {
			dp(y);
			f[x][1] += f[y][0];
			f[x][0] += max(f[y][0], f[y][1]);
		}
	}
}

int main() {
	read();
	long long ans = 0;
	for (int i = 1; i <= cnt; ++i) {
		long long part = 0;
		++vt;
		dp(rt1[i]);
		part = f[rt1[i]][0];

		++vt;		
		dp(rt2[i]);
		part = max(part, f[rt2[i]][0]);
		
		ans += part;
	}
	
	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) {
			dp(i);
			ans += max(f[i][0], f[i][1]);
		}
	}
	
	printf("%lld\n", ans);
	return 0;
}