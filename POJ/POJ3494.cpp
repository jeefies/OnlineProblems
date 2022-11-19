#include <stack>
#include <cstdio>
#include <iostream>

int m, n;
int mp[2000][2000];
bool getData() {
	if (scanf("%d %d", &m, &n) < 0) return false;
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &mp[i][j]);
			if (i > 0 && mp[i][j] != 0) mp[i][j] += mp[i - 1][j];
		}
	}
	
	return true;
}

int lineMax(int row) {
	static int ls[2000], rs[2000];
	
	int * h = mp[row];
	
	std::stack<int> stk;
	int hi;
	for (int i = 0; i < n; i++) {
		hi = h[i];
		while (!stk.empty() && h[stk.top()] >= hi) stk.pop();
		ls[i] = stk.empty() ? -1 : stk.top();
		stk.push(i); 
	}
	while (!stk.empty()) stk.pop();
	
	for (int i = n - 1; i >= 0; --i) {
		hi = h[i];
		while (!stk.empty() && h[stk.top()] >= hi) stk.pop();
		rs[i] = stk.empty() ? n : stk.top();
		stk.push(i); 
	}
	
	int maxs = 0;
	for (int i = 0; i < n; ++i) {
		maxs = std::max(maxs, (rs[i] - ls[i] - 1) * *(h++));
	}
	return maxs;
}

int proceed() {
	int maxs = 0;
	for (int row = 0; row < m; ++row) {
		maxs = std::max(maxs, lineMax(row));
	}
	
	return maxs;
}

int main() {
	while (getData()) {
		printf("%d\n", proceed());
	}
}
