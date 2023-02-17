#include <iostream> 
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;
#define N 2000006
#define S 26

int cnt[N], Q[N], head(0), tail(0);
int id[N], fail[N], kid[N][S], usage(0);

inline void insert(string &s, int pos) {
	int p = 0, j;
	for (auto &c : s) {
		j = c - 'a';
		if (!kid[p][j]) kid[p][j] = ++usage;
		p = kid[p][j];
		++cnt[p];
	}
	id[pos] = p;
}

inline void prepare(int root = 0) {
	for (int i(0), t; i < S; ++i) {
		if ((t = kid[root][i])) {
			fail[t] = root, Q[tail++] = t;
		}
	}
	
	int x;
	while (head ^ tail) {
		x = Q[head++];
		for (int i(0); i < S; ++i) {
			int &k = kid[x][i];
			if (k) {
				fail[k] = kid[fail[x]][i];
				Q[tail++] = k;
			} else { 
				k = kid[fail[x]][i];
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	
	string s;
	cin >> n;
	for (register int i(0); i < n ; ++i) {
		cin >> s;
		insert(s, i);
	} prepare();
	
	for (register int i(tail - 1); i; --i) {
		cnt[fail[Q[i]]] += cnt[Q[i]];
	}
	
	for (register int i(0); i < n; ++i) {
		printf("%d\n", cnt[id[i]]);
	}
	return 0;
}
