#include <iostream>

int n;
int cnt[10];
int types = 0;

// i [0, 9], i==10 && tot==n is end
void search(int i, int tot) {
	if (i == 10) {
		if (tot == n)
			types += 1;
		return;
	}
	
	if (tot + 10 - i > n || tot + (10 - i) * 3 < n) return;
	
	for (int k = 1; k <= 3; ++k) {
		cnt[i] = k;
		search(i + 1, tot + k);
	}
}

void output(int i, int tot) {
	if (i == 10) {
		if (tot == n) {
			for (int j = 0; j < 10; ++j) printf("%d ", cnt[j]);
			putchar('\n');
		}
		return;
	}
	
	if (tot + 10 - i > n || tot + (10 - i) * 3 < n) return;
	
	for (int k = 1; k <= 3; ++k) {
		cnt[i] = k;
		output(i + 1, tot + k);
	}
}

int main() {
	scanf("%d", &n);
	search(0, 0);
	printf("%d\n", types);
	output(0, 0);
}
