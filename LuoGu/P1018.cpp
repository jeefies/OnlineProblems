/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1018
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

#define NS sizeof(char)*50

typedef struct ha {
	int length;
	char nums[50];
} ha;

ha mul(ha & a, ha & b) {
	ha r = {0, {0}};
	memset(r.nums, 0, NS);

	for (int i = 0; i < a.length; i++) {
		for (int j = 0; j < b.length; j++) {
			r.nums[i + j] += a.nums[i] * b.nums[j];
			r.nums[i + j + 1] += r.nums[i + j] / 10;
			r.nums[i + j] %= 10;
		}
	}

	for (int i = a.length + b.length + 2; i >= 0; i--) {
		if (r.nums[i] != 0) {
			r.length = i + 1;
			break;
		}
	}
	return r;
}

bool bigger(ha & a, ha & b) {
	// isEqual = false;

	if (a.length > b.length) {
		return true;
	} else if (a.length < b.length) {
		return false;
	}

	for (int i = a.length - 1; i >= 0; i--) {
		if (a.nums[i] > b.nums[i]) return true;
		else if (a.nums[i] < b.nums[i]) return false;
	}

	// so equal here
	// isEqual = true;
	return false;
}

ha indexSlice(ha & n, int from, int to) {
	ha r = {to - from, {0}};
	for (int i = 0; i < r.length; i++) {
		r.nums[i] = n.nums[from + i];
	}
	return r;
}

ha dfs(ha & n, int k, int from) {
	if (k == 0) {
		ha r = indexSlice(n, from, n.length);
		return r;
	}

	ha maxn;
	maxn.length = 0;
	for (int i = from + 1; i < n.length - k + 1; i++) {
		ha left = indexSlice(n, from, i);
		ha right = dfs(n, k - 1, i);

		ha m = mul(left, right);
		if (bigger(m, maxn)) {
			maxn = m;
		}
	}

	return maxn;
}


int main() {
	int n, k;
	scanf("%d%d", &n, &k);

	getchar(); // ignore '\n'
	
	ha origin = {n, {0}};

	for (int i = n - 1; i >= 0; i--) {
		cin >> origin.nums[i];
		origin.nums[i] -= '0';
	}

	ha result = dfs(origin, k, 0);

	// putchar(result.length + 'a');
	// putchar(result.nums[0]);
	
	for (int i = result.length - 1; i >= 0; --i) {
		putchar('0' + result.nums[i]);
	}
	putchar('\n');
	return 0;
}
