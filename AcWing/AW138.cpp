#include <string>
#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned long long ull;
const int N = 1000000 + 10;
char s[N];
ull h[N], p[N] = {1}, P = 131;

ull get(int l, int r) {
	return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
	scanf("%s", s + 1);
	int n;
	cin >> n;
	
	int l = strlen(s + 1);
	for (int i = 1; i <= l; i++) {
		h[i] = h[i - 1] * P + s[i];
		p[i] = p[i - 1] * P;
	}
	
	for (int i = 1; i <= n; i++) {
		int l, r, L, R;
		cin >> l >> r >> L >> R; 
		if (get(l, r) == get(L, R)) printf("Yes\n");
		else printf("No\n");
	}
}
