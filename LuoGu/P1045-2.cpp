#include <iostream>
#include <cstring>
#include <cstdio>
// 包括了cmath才有log10这个函数！ 
#include <cmath>

using namespace std;

typedef long long Int;

// 为了不出现命名冲突，在全局的定义的用g作为前缀标志 
Int g_r[500] = {0};
// 简化memcpy时的代码 
#define numByte sizeof(Int)*500

void multi(Int* r, int x) {
	// 利用static减少栈空间的反复创建与释放 
	static Int tmp[501] = {0};
	
	// 清零，使用的是static！ 
	tmp[0] = 0;
	for (int i = 0; i < 500; i++) {
		// tmp[i] += r[i] * x;
		tmp[i] += r[i] << x;
		tmp[i + 1] = tmp[i] / 10;
		tmp[i] %= 10;
	}
	
	memcpy(r, tmp, numByte);
}

// 从后往前输出，每50位要记得换行 
void printLargeNum(Int* n) { 
	int cnt = 0;
	for (int i = 500 - 1; i >= 0; i--) {
		putchar(n[i] + '0');
		if (++cnt % 50 == 0) putchar('\n');
	}
}

int main() {
	int p = 3021377;
	cin >> p;
	cout << ceil(p * log10(2)) << endl;
	// 如果用printf,代码如注释
	// Int width = ceil(p * log10(2));
	// printf("%lld\n", width);

	// 一开始的时候要设置为乘法元，1	
	++g_r[0];
	
	int shiftBits = 59;
	while (p >= shiftBits) {
		multi(g_r, shiftBits); 
		p -= shiftBits;
	}
	
	// 处理剩下的位数 
	if (p) multi(g_r, p); 
	// 最后记得是求 2^n - 1 
	--g_r[0];
	printLargeNum(g_r);
}
