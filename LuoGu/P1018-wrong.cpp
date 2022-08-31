/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1018
 */

#error 这是一个不正确的思路的代码

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>

#define NS sizeof(char)*50

typedef struct ha {
	int length;
	char nums[50];
} ha;

ha mul(ha * a, ha * b) {
	ha r;
	memset(r.nums, 0, NS);

	for (int i = 0; i < a->length; i++) {
		for (int j = 0; j < b->length; j++) {
			r.nums[i + j] += a->nums[i] * b->nums[j];
			r.nums[i + j + 1] += r.nums[i + j] / 10;
			r.nums[i + j] %= 10;
		}
	}

	for (int i = 49; i >= 0; i--) {
		if (r.nums[i] != 0) {
			r.length = i + 1;
			break;
		}
	}
	return r;
}

bool bigger(ha * a, ha * b, bool & isEqual) {
	isEqual = false;

	if (a->length > b->length) {
		return true;
	} else if (a->length < b->length) {
		return false;
	}

	for (int i = a->length - 1; i >= 0; i--) {
		if (a->nums[i] > b->nums[i]) return true;
		else if (a->nums[i] < b->nums[i]) return false;
	}

	// so equal here
	isEqual = true;
	return false;
}

ha findMax(ha * num, int k) {
	ha a, b;
	ha ma, mb, mm;
	mm.length = 0;
	for (int i = 1; i < num->length; i++) {
		memset(a.nums, 0, NS);
		memset(b.nums, 0, NS);

		a.length = i;
		b.length = num->length - i;
		
		int ni = 0, counter = 0;
		while (counter < i) {
			a.nums[counter++] = num->nums[ni++];
		}
		counter = 0;
		while (counter < num->length - i) {
			b.nums[counter++] = num->nums[ni++];
		}
		
		ha r = mul(&a, &b);
		bool isEqual;
		if (bigger(&r, &mm, isEqual)) {
			mm = r;
			ma = a;
			mb = b;
		}
	}

	if (k == 1) return mm;


	bool isEqual;
	if (bigger(&ma, &mb, isEqual) || ma.length <= 1) {
		mb = findMax(&mb, k - 1);
	} else {
		ma = findMax(&ma, k - 1);
	}
	return mul(&ma, &mb);
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);

	getchar(); // ignore '\n'
	
	ha origin;
	origin.length = n;
	memset(origin.nums, 0, NS);

	for (int i = n - 1; i >= 0; i--) {
		origin.nums[i] = getchar() - '0';
	}

	// 偶然想到如果用二分贪心来做，能不能证明他的正确性？
	// 错误思路，fuck
	
	ha result = findMax(&origin, k);
	for (int i = result.length - 1; i >= 0; i--) {
		putchar('0' + result.nums[i]);
	}
	putchar('\n');
	return 0;
}
