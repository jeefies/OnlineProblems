#include <iostream>
#include <cstring>
#include <cstdio>
// ������cmath����log10��������� 
#include <cmath>

using namespace std;

typedef long long Int;

// Ϊ�˲�����������ͻ����ȫ�ֵĶ������g��Ϊǰ׺��־ 
Int g_r[500] = {0};
// ��memcpyʱ�Ĵ��� 
#define numByte sizeof(Int)*500

void multi(Int* r, int x) {
	// ����static����ջ�ռ�ķ����������ͷ� 
	static Int tmp[501] = {0};
	
	// ���㣬ʹ�õ���static�� 
	tmp[0] = 0;
	for (int i = 0; i < 500; i++) {
		// tmp[i] += r[i] * x;
		tmp[i] += r[i] << x;
		tmp[i + 1] = tmp[i] / 10;
		tmp[i] %= 10;
	}
	
	memcpy(r, tmp, numByte);
}

// �Ӻ���ǰ�����ÿ50λҪ�ǵû��� 
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
	// �����printf,������ע��
	// Int width = ceil(p * log10(2));
	// printf("%lld\n", width);

	// һ��ʼ��ʱ��Ҫ����Ϊ�˷�Ԫ��1	
	++g_r[0];
	
	int shiftBits = 59;
	while (p >= shiftBits) {
		multi(g_r, shiftBits); 
		p -= shiftBits;
	}
	
	// ����ʣ�µ�λ�� 
	if (p) multi(g_r, p); 
	// ���ǵ����� 2^n - 1 
	--g_r[0];
	printLargeNum(g_r);
}
