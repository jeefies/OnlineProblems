#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <string>

using namespace std;
const int N = 300007;

class Trie {
private:
	struct Node {
		int kids[26], cnt;
	} nodes[N];
	int usage;
	int in[26], G[26][26];
public:
	Trie() : usage(01) {}
	
	#define discrete(c) (c - 'a')
	#define kids(p, j) nodes[p].kids[j]
	#define cnt(p) nodes[p].cnt
	void insert(string s, int len) {
		int p = 1;
		for (int i = 0; i < len; ++i) {
			int j = discrete(s[i]);
			if (!kids(p, j)) kids(p, j) = ++usage;
			p = kids(p, j);
		}
		++cnt(p);
	}
	
	void topSort() {
		deque<int> q; q.clear();
		for (int i = 0; i < 26; ++i) {
			if (in[i] == 0) q.push_back(i);
		}
		
		while (q.size()) {
			int x = q.front(); q.pop_front();
			for (int y = 0; y < 26; ++y) {
				if (G[x][y] && --in[y] == 0) q.push_back(y);
			}
		}
	}
	
	bool find(string s, int len) {
		// clear
		memset(G, 0, sizeof(G));
		memset(in, 0, sizeof(in));
		
		int p = 1;
		for (int i = 0; i < len; ++i) {
			if (cnt(p)) return false; // be one's prefix, no way
			int x = discrete(s[i]);
			// check for others
			for (int y = 0; y < 26; ++y) {
				if (x != y && kids(p, y) && !G[x][y]) {
					G[x][y] = 1;
					++in[y];
				}
			}
			p = kids(p, x);
		}
		topSort();
		for (int i = 0; i < 26; ++i) {
			if (in[i]) return false;
		}
		return true;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(false);
	 
	static Trie trie;
	static string strs[N];
	static bool valid[N];
	int n;
	
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> strs[i];
		trie.insert(strs[i], strs[i].size());
		valid[i] = false;
	}
	
	int res(0);
	for (int i = 0; i < n; ++i) {
		if (trie.find(strs[i], strs[i].size())) {
			valid[i] = true, ++res;
		}
	}
	cout << res << endl;
	for (int i = 0; i < n; ++i) {
		if (valid[i]) cout << strs[i] << endl;
	}
	return 0;
}
