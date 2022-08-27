#include <cstdio>
#include <stdint.h>

const int MOD = 10007;
int64_t Cni[1000002] = {1};

int lucas(int n, int i, int p) {
	int ret = 1;
	while (i) {
		
	}
}

int main() {
	int k;
	scanf("%d", &k);
	int n = k - 1;
	
	// C(n, i) = C(n, i - 1) * (n - i + 1) / i
	for (int i = 1; i <= (k + 1) / 2; i++) {
		Cni[i] = (Cni[i - 1] * (n - i + 1) / i) % MOD;
	}
	
	// for (int i = 0; i <= (k + 1) / 2; i++) {
	 	// printf("%lld ", Cni[i]);
	// }
	// putchar('\n');
	
	int64_t sum;
	// 奇数 
	for (int i = 1; i <= (k + 1) / 2; i++) {
		// printf("add %d * %d\n", Cni[i - 1], i * 2 - 1);
		sum = (sum + Cni[i - 1] * (i * 2 - 1)) % MOD;
	}
	// printf("Odd ok, start Even\n");
	// 偶数应该比奇数少一或相等 
	for (int i = 1; i <= k / 2; i++) {
		// printf("add %d * %d\n", Cni[i - 1], i * 2);
		sum = (sum + Cni[i - 1] * i * 2) % MOD;
	}

	printf("%lld\n", sum);
}
