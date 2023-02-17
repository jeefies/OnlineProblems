#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

typedef long long data;

const int N = 1e5 + 7;

data pre[N];
data target[N];

data readL() {
	data x = 0, f = 1; char tmp;
	do {
		if ((tmp = getchar()) == '-') f = -1;
	} while (tmp < '0' || '9' < tmp);
	do {
		x = x * 10 + tmp - '0', tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	return x * f;
}

data n;
void read() {
	n = readL();
	
	for (int i = 1; i <= n; ++i) {
		pre[i] = readL() + pre[i - 1];
		target[i] = pre[i];
	}
	std::sort(target + 1, target + n + 1);
}

int main() {
	read();
	if (target[1] <= 0 || target[n] != pre[n]) {
		printf("-1\n");
		return 0;
	}
	
	std::map<data, int> ti;
	for (int i = 1; i <= n; ++i) {
		if (target[i] == target[i - 1]) return printf("-1\n"), 0;
		ti[target[i]] = i;
	}
	
	data pi, ans = 0;
	for (int i = 1; i <= n; ++i) {
		while (i != ti[(pi = pre[i])]) {
			++ans;
			std::swap(pre[i], pre[ti[pi]]);
		}
	}
	
	printf("%lld\n", ans);
	return 0;
}