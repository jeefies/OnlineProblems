#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
const int N = 2e6 + 7;

int pos[N], cnt[N];
vector<int> G[N];

class ACAutomaton {
public:
	struct Node {
		int kids[27];
		int fail, id;
	} nodes[N];
	int usage;
	ACAutomaton() : usage(0) { }
	
	#define id(p) nodes[p].id
	#define kids(p, j) nodes[p].kids[j]
	#define fail(p) nodes[p].fail
	#define discrete(c) (c-'a')
	void insert(string s, int id) {
		int len = s.size(), p = 0;
		for (int i(0); i < len; ++i) {
			int j = discrete(s[i]);
			if (!kids(p, j)) kids(p, j) = ++usage;
			p = kids(p, j);
		}
		pos[id] = p;
	}
	
	void build() {
		queue<int> Q;
		for (int i(0); i < 27; ++i) {
			if (kids(0, i))
				fail(kids(0, i)) = 0, Q.push(kids(0, i));
		}
		
		while (!Q.empty()) {
			int x = Q.front(); Q.pop();
			for (int i(0); i < 27; ++i) {
				if (kids(x, i)) {
					fail(kids(x, i)) = kids(fail(x), i);
					Q.push(kids(x, i));
				} else {
					kids(x, i) = kids(fail(x), i);
				}
			}
		}
		
		for (int i(1); i <= usage; ++i) G[fail(i)].push_back(i);
	}
	
	void ACMatch(string s, int * cnt) {
		int len = s.size(), p = 0;
		for (int i(0); i < len; ++i) {
			p = kids(p, discrete(s[i]));
			for (int q = p; q; q = fail(q)) {
				if (id(q)) ++cnt[id(q)];
			}
		}
	}
	
	void dfs(int x) {
		for (auto &y : G[x]) {
			if (x ^ y) {
				dfs(y);
				cnt[x] += cnt[y];
			}
		}
	}
} AC;

int main() {
	int n;
	string S, tmp;
	
	cin >> n;
	for (int i(1); i <= n; ++i) {
		cin >> tmp;
		AC.insert(tmp, i);
		tmp.push_back('z' + 1);
		S = S + tmp;
	} AC.build();
	
	int p(0);
	for (auto &c : S) {
		p = AC.nodes[p].kids[c - 'a'], ++cnt[p];
	}
	AC.dfs(0);
	for (int i(1); i <= n; ++i) {
		cout << cnt[pos[i]] << '\n';
	} cout << flush;
	return 0;
}
