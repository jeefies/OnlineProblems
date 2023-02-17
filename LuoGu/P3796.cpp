#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 153, L = 70;

class ACAutomaton {
private:
	struct Node {
		int kids[26];
		int fail, id;
	} nodes[N * L];
	int usage;
public:
	ACAutomaton() : usage(1) { }
	inline void clear() {
		memset(nodes, 0, sizeof(Node) * (usage + 1));
		usage = 1;
	}
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
		id(p) = id;
	}
	
	void build() {
		queue<int> Q;
		for (int i(0); i < 26; ++i) {
			if (kids(0, i))
				fail(kids(0, i)) = 0, Q.push(kids(0, i));
		}
		
		while (!Q.empty()) {
			int x = Q.front(); Q.pop();
			for (int i(0); i < 26; ++i) {
				if (kids(x, i)) {
					fail(kids(x, i)) = kids(fail(x), i);
					Q.push(kids(x, i));
				} else {
					kids(x, i) = kids(fail(x), i);
				}
			}
		}
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
} AC;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	int n;
	string strs[N];
	int cnt[N]; 
	while (true) {
		cin >> n;
		if (!n) break;
		
		AC.clear();
		std::fill(cnt + 1, cnt + n + 1, 0);
		for (int i(1); i <= n; ++i) {
			cin >> strs[i];
			AC.insert(strs[i], i);
		}
		AC.build();
		
		cin >> strs[0];
		AC.ACMatch(strs[0], cnt);
		int mcnt(0);
		for (int i(1); i <= n; ++i) {
			if (cnt[i] > mcnt) mcnt = cnt[i];
		}
		cout << mcnt << '\n';
		for (int i(1); i <= n; ++i) {
			if (cnt[i] == mcnt) cout << strs[i] << '\n';
		}
	}
	cout << flush;
	return 0;
}
