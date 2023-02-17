#include <stdio.h>

#define N 3007

int n;
int s[N], l[N], r[N];

int main() {
	scanf("%d", &n);
	char tmp;
	do {
		tmp = getchar();
	} while (tmp != '.' && tmp != 'L' && tmp != 'R');
	
	s[1] = tmp;
	for (int i = 2; i <= n; ++i) s[i] = getchar();
	
	int mark = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'R') mark = i;
		r[i] = mark;
		if (s[i] == 'L') mark = 0;
	}
	
	mark = 0;
	for (int i = n; i >= 1; --i) {
		if (s[i] == 'L') mark = i;
		l[i] = mark;
		if (s[i] == 'R') mark = 0;
	}
	
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (
			(l[i] == r[i] && l[i] == 0) ||
			(l[i] != 0 && r[i] != 0 && l[i] + r[i] == i * 2)
		) {
			++res;
		}
	}
	
	printf("%d\n", res);
	
	return 0;
}