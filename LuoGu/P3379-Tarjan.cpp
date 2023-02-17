#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

const int N = 5e5 + 7;

struct Edge {
	int to, next;
} edge[N * 2];
// typedef struct Edge Edge;
int head[N], tot = 0;

void add(int u, int v) {
	++tot;
	edge[tot] = {v, head[u]}, head[u] = tot;
}

int readInt() {
	char tmp;
	int x = 0, f = 1;
	do {
		tmp = getchar();
		if (tmp == '-') f = -1;
	} while (tmp < '0' || tmp > '9');
	do {
		x = x * 10 + tmp - '0';
		tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	return x * f;
}

int n, q, root;
std::vector<int> ques[N], quesID[N];
int res[N];
int grp[N];
void read() {
	n = readInt(), q = readInt(), root = readInt();
	
	int u, v;
	for (int i = 1; i < n; ++i) {
		u = readInt(); v = readInt();
		add(u, v), add(v, u);
		grp[i] = i;
	}
	
	for (int i = 1; i <= q; ++i) {
		u = readInt(); v = readInt();
		if (u == v) {
			res[i] = u;
		} else {
			ques[u].push_back(v), quesID[u].push_back(i);
			ques[v].push_back(u), quesID[v].push_back(i);
		}
	}
}

int find(int x) {
	if (x != grp[x]) return grp[x] = find(grp[x]);
	return x;
}

int mark[N];
void tarjan(int x) {
	mark[x] = 1;
	for (int y, i = head[x]; i; i = edge[i].next) {
		y = edge[i].to;
		if (mark[y]) continue;
		tarjan(y);
		grp[y] = x;
	}
	for (int y, id, i = 0; i < ques[x].size(); ++i) {
		y = ques[x][i], id = quesID[x][i];
		if (mark[y] == 2) {
			res[id] = find(y);
		}
	}
	mark[x] = 2;
}

int main() {
	read();
	tarjan(root);
	for (int i = 1; i <= q; ++i) {
		printf("%d\n", res[i]);
	}
	return 0;
}