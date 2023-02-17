#include <stdio.h>
#include <string.h>

#define N 600007
#define S 26

long long max(long long a, long long b) {
	return a > b ? a : b;
}

char s[N];

int usage, pos, last; 
int kids[N][S], exi[N], fail[N], len[N];

void init() {
	usage = 2, pos = 0, last = 1;
	len[2] = 0, len[1] = -1, fail[2] = 1;
}

inline int up(int p) {
	while (s[pos - len[p] - 1] != s[pos])
		p = fail[p];
	return p;
}

inline int insert(int c) {
	int p = up(last), &q = kids[p][c];
	if (!q) {
		q = ++usage;
		len[q] = len[p] + 2;
		fail[q] = p == 1 ? 2 : kids[up(fail[p])][c];
	}
	++exi[last = q];
	return ++pos;
}

long long count() {
	long long maxn(0);
	for (int k = usage; k; --k) {
		exi[fail[k]] += exi[k];
		maxn = max(maxn, (long long)exi[k] * len[k]);
	}
	return maxn;
}

int main() {
	scanf("%s", s);
	int n = strlen(s);
	
	init();
	for (int i = 0; i < n; ++i) {
		insert(s[i] - 'a');
	}
	
	printf("%lld\n", count());
	return 0;
}
