#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

#define MAXN 1001
#define MAXI 500
#define NUMSIZE sizeof(base)
int base[MAXN], nums[MAXN], tmp[MAXN], p;

void multi() {
	// nums����base 
	memset(tmp, 0, NUMSIZE);
	
	for (int i = 0; i < MAXI; i++) {
		for (int j = 0; j < MAXI; j++)
			tmp[i + j] += nums[i] * base[j];
	}

	for (int i = 0; i < MAXI; i++) {
		tmp[i + 1] += tmp[i] / 10;
		tmp[i] %= 10;
	}
	
	memcpy(nums, tmp, NUMSIZE);
}

void updatebase() {
	// base * base 
	memset(tmp, 0, NUMSIZE);

	for (int i = 0; i < MAXI; i++) {
		for (int j = 0; j < MAXI; j++)
			tmp[i + j] += base[i] * base[j];
	}

	for (int i = 0; i < MAXI; i++) {
		tmp[i + 1] += tmp[i] / 10;
		tmp[i] %= 10;
	}
	
	memcpy(base, tmp, NUMSIZE);
}

void printLargeNum(int * n) { 
	int cnt = 0;
	for (int i = 500 - 1; i >= 0; i--) {
		putchar(n[i] + '0');
		if (++cnt % 50 == 0) putchar('\n');
	}
}

int main() {
	cin >> p;
	cout << ceil(p * log10(2)) << endl;
	
	// ��Ϊ�˷�Ԫ��1 
	nums[0] = 1;
	// ��2��1�η�Ϊ��ʼֵ 
	base[0] = 2;
	while (p > 0) {
		if (p % 2 == 1) // ��Ҫ��һ��base 
			multi();
		p /= 2;
		updatebase();
	}
	
	// ���ǵ����� 2^n - 1 
	nums[0] -= 1;
	printLargeNum(nums);
	return 0;
}
