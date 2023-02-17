#include <iostream>

const int N = 1e5 + 7;

inline int max(int a, int b) {
	return a > b ? a : b;
}

#define lowbit(i) (i&-i)
class BIT {
private:
	int b[N];
public:
	void update(int i, int x) {
		for (; i < N; i += lowbit(i)) {
			b[i] = max(b[i], x);
		}
	}
	
	int query(int i) {
		int r = 0;
		for (; i; i -= lowbit(i)) {
			r = max(r, b[i]);
		}
		return r;
	}
};

int n;
int a[N], b[N];

void read() {
	scanf("%d", &n);
	
	int v;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v);
		b[v] = i;
	}
	
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v);
		a[i] = b[v];
	}
}

int LIS() {
	int ans = 0;
	BIT bit;
	for (int i = 1; i <= n; ++i) {
		int len = bit.query(a[i]) + 1;
		ans = max(ans, len);
		bit.update(a[i], len);
	}
	return ans;
}

int main() {
	read();
	printf("%d", LIS());
	return 0;
}
