#include <iostream>

const int MOD = 10007;
int nums[1000002];

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < (n + 1) / 2; i++) {
		nums[i] = i * 2 + 1;
	}
	
	for (int i = 0; i < n / 2; i++) {
		nums[n - 1 - i] = i * 2 + 2;
	}
	
	for (int i = 0; i < n - 1; i++) {
		for (int x = 0; x < n - i - 1; x++) {
			nums[x] = (nums[x] + nums[x + 1]) % MOD;
//			printf("x = %d\n", x);
		}
//		printf("Loop end\n");
//		for (int ij = 0; ij < n; ij++) printf("%d ", nums[ij]);
//		putchar('\n');
	}
	
	printf("%d\n", nums[0]);
	
}
