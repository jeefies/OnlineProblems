#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

class Trie {
private:
	struct Node {
		int kids[65];
		int cnt;
	} nodes[3000007];
	int usage, root;
public:
	Trie() : usage(0) { clear(); }
	
	void clear() {
		memset(nodes, 0, sizeof(Node) * (usage + 1));
		usage = root = 1;
	}
	
	char discrete(char c) {
		if ('0' <= c && c <= '9') return c - '0';
		else if ('a' <= c && c <= 'z') return c - 'a' + 10;
		else return c - 'A' + 36;
		return -1; // Never reached!
	}
	
	#define kids(p, j) nodes[p].kids[j]
	#define cnt(p) nodes[p].cnt
	void insert(char * s, int len) {
		int p = 1;
		for (int i = 0; i < len; ++i) {
			int j = discrete(s[i]);
			if (!kids(p, j)) kids(p, j) = ++usage;
			p = kids(p, j), ++cnt(p);
		}
	}
	
	int preCount(char * s, int len) {
		int p = 1;
		for (int i = 0; i < len; ++i) {
			int j = discrete(s[i]);
			if (!kids(p, j)) return 0;
			p = kids(p, j);
		}
		return cnt(p);
	}
};

inline void proc() {
	static Trie trie; trie.clear();
	int n, q;
	cin >> n >> q;
	
	static char s[3000006];
	for (int i(0), ol(0); i < n; ++i) {
		cin >> s;
		ol = strlen(s);
		trie.insert(s, ol);
	}
	
	for (int i(0), ol(0); i < q; ++i) {
		cin >> s;
		ol = strlen(s);
		cout << trie.preCount(s, ol) << endl;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int T;
	cin >> T;
	while (T--) {
		proc();
	}
	return 0;
}
