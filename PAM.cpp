#include <stdio.h>
#include <string.h>

#define N 500007
#define S 26

int last, cnt, pos;
int kids[N][S], len[N], fail[N], dep[N];

char s[N];

inline void init() {
	last = 1, pos = 0, cnt = 2;
	len[2] = 0, fail[2] = 1;
	len[1] = -1;
}

int up(int p) {
	// printf("Upping %d\n", p);
	while (s[pos - 1 - len[p]] != s[pos])
		p = fail[p];
	return p;
}

void insert(int c) {
	++pos;
	int p = up(last), &q = kids[p][c];
	if (!q) {
		q = ++cnt;
		len[q] = len[p] + 2;
		fail[q] = p == 1 ? 2 : kids[up(fail[p])][c];
		dep[q] = dep[fail[q]] + 1;
	}
	last = q;
}

int main() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	
	int k = 0;
	init();
	for (int i = 1; i <= n; ++i) {
		s[i] = (s[i] - 97 + k) % 26 + 97;
		insert(s[i] - 'a');
		printf("%d ", (k = dep[last]));
	}
	return 0;
}
