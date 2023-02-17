#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>

using namespace std;

class Edge {
public:
	int to, w;
	constexpr Edge(int to, int w) : to(to), w(w) { }
};

const int N = 1e5 + 7;

vector<Edge> G[N];
int du[N], stk[N], top(0);
double E[N], ans(0.0);

void tops() {
	deque<int> st;
	st.push_back(1);
	while (st.size()) {
		int x = st.back(), siz = (int)G[x].size(); st.pop_back();
		for (auto &e : G[x]) {
			if (--du[e.to] == 0) st.push_back(e.to);
			E[e.to] += E[x] / siz;
			ans += (E[x] * e.w / siz);
		}
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	int u, v, w;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		G[u].push_back(Edge(v, w));
		++du[v];
	}
	E[1] = 1.0;
	tops();
	printf("%.2lf", ans);
	return 0;
}