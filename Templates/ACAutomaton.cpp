#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;
const int N = 1e6 + 7;

class ACAutomaton {
private:
	struct Node {
		int kids[26];
		int fail, cnt;
	} nodes[N];
	int usage;
public:
	ACAutomaton() : usage(0) {
	}
	#define discrete(c) ((c)-'a')
	#define kids(p, j) (nodes[p].kids[j])
	#define cnt(p) (nodes[p].cnt)
	#define fail(p) (nodes[p].fail)
	void insert(string s) {
		int len = s.size(), p = 0;
		for (int i = 0; i < len; ++i) {
			int j = discrete(s[i]);
			if (!kids(p, j)) kids(p, j) = ++usage;
			p = kids(p, j);
		}
		++cnt(p);
	}
	
	void procFail() {
		queue<int> Q;
		for (int i = 0; i < 26; ++i) {
			if (kids(0, i))
				fail(kids(0, i)) = 0, Q.push(kids(0, i));
		}
		
		while (Q.size()) {
			int x = Q.front(); Q.pop();
			for (int i = 0; i < 26; ++i) {
				if (kids(x, i)) {
					fail(kids(x, i)) = kids(fail(x), i);
					Q.push(kids(x, i));
				} else {
					kids(x, i) = kids(fail(x), i);
				}
			}
		}
	}
	
	int ACMatch(string s) {
		int len = s.size(), p(0), ans(0);
		for (int i = 0; i < len; ++i) {
			p = kids(p, discrete(s[i]));
			for (int t = p; t && ~cnt(t); t = fail(t)) {
				ans += cnt(t), cnt(t) = -1;
			}
		} 
		return ans;
	}
} AC;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	 
	int n;
	string S;
	
	cin >> n;
	for (int i = 0; i ^ n; ++i) {
		cin >> S;
		AC.insert(S);
	}
	
	AC.procFail();
	cin >> S;
	cout << AC.ACMatch(S) << endl;
	return 0; 
}
