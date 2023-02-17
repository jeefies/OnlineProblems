#include <stdio.h>
#include <string.h>

#define N 1000006

int P[N];
char s[N];

inline int min(int x, int y) {
	return x < y ? x : y;
}
inline int max(int x, int y) {
	return x > y ? x : y;
}

void proc() {
	memset(s, 0, sizeof(s));
	memset(P, 0, sizeof(P));
	
	char tmp;
	do tmp = getchar(); while (tmp < 'a' || tmp > 'z');
	s[0] = '^', s[1] = '#';
	int n = 2;
	do s[n++] = tmp, s[n++] = '#', tmp = getchar(); while ('a' <= tmp && tmp <= 'z');
	
	int ans(0);
	int M(0), R(0), p;
	for (int i(1); i < n; i += 2) {
		p = R > i ? min(R - i + 1, P[(M<<1) - i]) : 1;
		while (s[i + p] == s[i - p]) ++p; // ��������չ 
		if (i + p - 1 > R) M = i, R = i + p - 1; // ���±߽�
		P[i] = p;		
	}
	// Ѱ�Ҵ�
	for (int i(1); i < n; i += 2) {
		int p = P[i] / 2 + 1;
		for (int r(ans); r < p; r += 2) {
			if (P[i + r] > r && P[i - r] > r) ans = r;
		}
	}
	printf("%d\n", ans + ans);
}

int main() {
	int T; 
	scanf("%d", &T);
	while (T--) {
		proc();
	}
	return 0;
}
