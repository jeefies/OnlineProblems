#include <cstdio>

int n, m;
int k[2007], a[2007];
int t[100007], mt = 0;
bool dp[500007] = {true};

int main() {
	scanf("%d %d", &n, &m);
	
	int ki, ai, p = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &ki, &ai);
		
		int base = 1;
		while (base < ai) {
			k[p] = ki * base, a[p] = base, ++p;
			ai -= base, base <<= 1;
		}
		k[p] = ki * ai, a[p] = ai, ++p;
	}
	
	for (int i = 0; i < m; ++i) {
		scanf("%d", t + i);
		if (t[i] > mt) mt = t[i];
	}
	
	for (int i = 0; i < p; ++i) {
		int ki = k[i];
		for (int i = mt; i >= ki; --i) {
			if (dp[i - ki]) dp[i] = true;
		}
	}
	
	for (int i = 0; i < m; ++i) {
		if (dp[t[i]]) puts("Yes");
		else puts("No");
	}
	
	return 0;
}