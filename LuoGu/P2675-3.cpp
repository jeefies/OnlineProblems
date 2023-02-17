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
	
    // 5合1
    while (n >= 5) {
        for (int i = 0; i + 4 < n; ++i) {
            nums[i] = (nums[i] + nums[i+4] + ((nums[i+1] + nums[i+2] + nums[i+3]) << 2) % MOD + (nums[i+2]<<1)) % MOD;
        }
        n -= 4;
    }

    // 2合1
    while (n >= 2) {
        for (int i = 0; i + 1 < n; ++i) {
            nums[i] = (nums[i] + nums[i + 1]) % MOD;
        }
        n -= 1;
    }

	printf("%d\n", nums[0]);
	
}