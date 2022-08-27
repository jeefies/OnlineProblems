#include <iostream>
#include <string.h>

const int MOD = 19260817;
const int MAXN = 1002;
int m[MAXN+2][MAXN+2];
int f[MAXN+2][MAXN+2];

int main() {
	memset(m, 0, sizeof(f));
	memset(f, 0, sizeof(f));
	
	f[0][0] = 1;
	for (int i = 1; i <= MAXN; i++) {
		f[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % MOD;
		}
	}
	
	m[0][0] = 1;
	for (int i = 1; i <= MAXN; i++) {
		m[i - 1][0] = f[i][1];
		for (int j = 2; j <= MAXN; j++) {
			m[i - 1][j - 1] = (f[i][j] + m[i - 1][j - 2]) % MOD;
		}
	}
	
	for (int j = 0; j <= MAXN; j++) {
		for (int i = 1; i <= MAXN; i++) {
			m[i][j] = (m[i][j] + m[i - 1][j]) % MOD;
		}
	}
	
	int k;
	scanf("%d", &k);
	while (--k >= 0) {
		int i, j;
		scanf("%d%d", &i, &j);
		if (j <= i)
			printf("%d\n", m[j - 1][i - 1]);
		else printf("0\n");
	}
	
}
